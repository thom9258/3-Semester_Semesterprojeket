#include "PhysicalLayer.h"
#include <iostream>
#include <array>
#include <bitset>
#include <chrono>     
#include <ctime> 
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>

#define M_PI 3.1415926535
#define SUBSAMPLE 2750
#define SAMPLE_RATE_LISTEN 44100

//--------------------------------------------------------------------------------------
//-------------------------------------constructors-------------------------------------
//--------------------------------------------------------------------------------------
PhysicalLayer::PhysicalLayer() {
	buffersize = 0xFFFF;
	setProcessingInterval(sf::milliseconds(100));//default is 100
	tail = 0;
	head = 0;
	listen = true;
}

//--------------------------------------------------------------------------------------

PhysicalLayer::~PhysicalLayer() {
	stop();
	listen = false;
	sf::sleep(sf::milliseconds(20));
	//std::cout << "DESTRUCTOID" << std::endl; //Debugging
}

//--------------------------------------------------------------------------------------
//----------------------------------Practical function----------------------------------
//--------------------------------------------------------------------------------------

//finding frequency from nibble and save frequency to given array 
template<typename arrayType, typename intType>
void nipplesToFreq(intType nipple, arrayType& arr) { //nipple, saveToArray
	switch (nipple & 0b0011) {
	case 0b0000:
		*std::begin(arr) = 1209;
		break;
	case 0b0001:
		*std::begin(arr) = 1336;
		break;
	case 0b0010:
		*std::begin(arr) = 1477;
		break;
	case 0b0011:
		*std::begin(arr) = 1633;
		break;
	}

	switch (nipple & 0b1100) {
	case 0b0000:
		*(std::end(arr) - 1) = 697;
		break;
	case 0b0100:
		*(std::end(arr) - 1) = 770;
		break;
	case 0b1000:
		*(std::end(arr) - 1) = 852;
		break;
	case 0b1100:
		*(std::end(arr) - 1) = 941;
		break;
	}
}

//finding corresponding nibble to the given frequencies
void freqToNipples(std::vector<float> freq, std::array<int, 4>& resultNipple) {
	std::vector<int> freq2(freq.begin(), freq.end());
	switch (freq2[0]) {
	case 697:
		resultNipple[0] = 0b0;
		resultNipple[1] = 0b0;
		break;
	case 770:
		resultNipple[0] = 0b0;
		resultNipple[1] = 0b1;
		break;
	case 852:
		resultNipple[0] = 0b1;
		resultNipple[1] = 0b0;
		break;
	case 941:
		resultNipple[0] = 0b1;
		resultNipple[1] = 0b1;
		break;
	}

	switch (freq2[1]) {
	case 1209:
		resultNipple[2] = 0b0;
		resultNipple[3] = 0b0;
		break;
	case 1336:
		resultNipple[2] = 0b0;
		resultNipple[3] = 0b1;
		break;
	case 1477:
		resultNipple[2] = 0b1;
		resultNipple[3] = 0b0;
		break;
	case 1633:
		resultNipple[2] = 0b1;
		resultNipple[3] = 0b1;
		break;
	}
}

void playTune(std::vector<std::array<double, 2>> TUNES, float BPS = 1, unsigned int AMPLITUDE = 5000) {
	const unsigned toneCount = TUNES.size();
	const unsigned SAMPLES = 88200;
	unsigned SAMPLE_RATE = (SAMPLES / toneCount) * BPS;
	int samplePerTone = SAMPLES / toneCount;

	sf::Int16 raw[SAMPLES];
	float incrementX;
	float incrementY;
	float x = 0, y = 0;		//sine funktion variable  
	sf::SoundBuffer Buffer;		//define sound buffer
	sf::Sound Sound;			//define Sound output
	//sf::OutputSoundFile FILE;	//define file
	x = 0;
	y = 0;
	const double TWO_PI = 6.28318;
	for (unsigned int j = 0; j < toneCount; j++)
	{
		unsigned start = (samplePerTone)*j;
		unsigned slut = (j + 1) * (samplePerTone);


		//generate sine function
		for (unsigned i = start; i < slut; i++) { // loop for every sample
			//double window = sin(i*M_PI/(slut-start));																			//sine window funktion source:Claus
			//double window = asin(sin(i*M_PI / (slut - start)));																//triangular source:Claus
			//double window = 0.5 * (1 - cos(2 * M_PI*i / (slut-start)));														//Hann window function source:https://stackoverflow.com/questions/3555318/implement-hann-window
			//double window = 0.42 - 0.5*cos(2 * M_PI*i / ((slut - start) - 1)) + 0.08*cos(4 * M_PI*i / ((slut - start) - 1));	//blackman source matlab
			double window = 0.5 * (1 - cos(2 * M_PI * i / (slut - start)));													//hamming window function
			raw[i] = window * (AMPLITUDE * sin(x * TWO_PI) + AMPLITUDE * sin(y * TWO_PI));
			x += TUNES[j][0] / SAMPLE_RATE;
			y += TUNES[j][1] / SAMPLE_RATE;

		}

		//load sound to bufffer

		//std::cout << "playing sound " << TUNES[j][0] << " and " << TUNES[j][1] << "\n"; //Debugging

	}
	// Error message if loading failed
	if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
		std::cerr << "Loading failed!" << std::endl;
	}

	Sound.setBuffer(Buffer);
	Sound.play();
	sf::sleep(sf::seconds((toneCount / BPS)));
}

//--------------------------------------------------------------------------------------

void transmit(std::vector<int> fraDataLink) {
	

}



//--------------------------------------------------------------------------------------
//----------------------------------------Sender----------------------------------------
//--------------------------------------------------------------------------------------

void PhysicalLayer::sendNippleCount(std::vector<int> bitString, float BPS) {
	//sending nibble count
	unsigned short nippleCount;
	nippleCount = bitString.size() / 4;

	std::array<double, 2> arr;
	std::vector<std::array<double, 2>> TUNES;

	for (int i = 0; i < 2; i++) {
		nipplesToFreq(nippleCount, arr);
		TUNES.push_back(arr);
		nippleCount = nippleCount >> 4;
	}
	//output sound
	std::reverse(TUNES.begin(), TUNES.end());
	playTune(TUNES, BPS);
}

void PhysicalLayer::sendBitString(std::vector<int> bitString, float BPS) {
	std::array<double, 2> arr;
	std::vector<std::array<double, 2>> TUNES;

	//send nibble count
	unsigned short nippleCount;
	nippleCount = bitString.size() / 4;



	for (int i = 0; i < 2; i++) {
		nipplesToFreq(nippleCount, arr);
		TUNES.push_back(arr);
		nippleCount = nippleCount >> 4;
	}
	//output sound
	std::reverse(TUNES.begin(), TUNES.end());

	//send data
	std::reverse(bitString.begin(), bitString.end());
	std::vector<int> nipples;
	for (int i = 0; i < bitString.size(); i += 4) {
		int temp = 0;
		for (int j = 3; j >= 0; j--) {
			temp = temp << 1;
			temp += bitString[j + i];
		}
		nipples.push_back(temp);
	}
	std::reverse(nipples.begin(), nipples.end());

	//std::array<double, 2> arr;
	//std::vector<std::array<double, 2>> TUNES;

	for (int i = 0; i < nipples.size(); i++) {
		nipplesToFreq(nipples[i], arr);
		TUNES.push_back(arr);
	}

	//output sound
	playTune(TUNES, BPS);
}

//--------------------------------------------------------------------------------------

void PhysicalLayer::sendStartBit(int startBit, int count, float BPM) {
	//play sound
	int k = startBit;
	std::array<double, 2> arr;
	std::vector<std::array<double, 2>> TUNES;
	nipplesToFreq(k, arr);
	TUNES.push_back(arr);
	for (int i = 0; i < count; i++) {
		playTune(TUNES, BPM);
		sf::sleep(sf::seconds(1 / BPM));
	}

	TUNES.clear();
	k = 0b0001;
	nipplesToFreq(k, arr);
	TUNES.push_back(arr);
	playTune(TUNES, BPM);
	//sf::sleep(sf::seconds(1 / BPM));
};



//--------------------------------------------------------------------------------------
//---------------------------------------Receiver---------------------------------------
//--------------------------------------------------------------------------------------

//SFML's sample function. (recorder calls this function every 100 ms)
bool PhysicalLayer::onProcessSamples(const int16_t* samples, std::size_t sampleCount) {
	for (int i = 0; i < sampleCount; i++) {
		if (head + 1 >= buffersize)
			head = 0;
		buffer[head++] = ((*(samples + i)));
	}
	return listen;
}

//returns the value at tail. part of our circle buffer.
float PhysicalLayer::tailBuffer() {
	while (tail + 2 > head&& head - tail > 0 || ((tail + 1 == buffersize) && head < 2)) {
		;
	}
	if (tail + 1 >= buffersize) {
		tail = 0;
	}

	return buffer[tail++];
}

// this function listens for our startbit
bool PhysicalLayer::listenStartBit(int sleepTime) {
	bool downSlope = false;

	std::array<float, 2> prevRes = { 0,0 };
	std::array<float, 2> currRes = { 0,0 };

	int DTMFfreq[] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	
	std::vector<float> highFreq;
	highFreq.resize(8);

	std::vector<float> samples;
	samples.resize(SUBSAMPLE);

	listen = true;

	int numSamples = 44100 / 2; // expected tone time in samples. here we send 1 tone and 1 pause per second
	int wait = (SAMPLE_RATE_LISTEN/4) + (SAMPLE_RATE_LISTEN/2); // used to synchronize after peak found. we wait 1/4 of a tone + the pause 
	int windowRotate = 100; // how much we move our window 
	float threshold = 300.0f; // tested threshold for our goertzel magnitudes. tested at 35 cm distance

	while (true) {
		//here we wait by updating our tail
		for (int i = 0; i < SUBSAMPLE; i++) {
			samples[i] = tailBuffer();
		}

		while (true) {
			//window move
			std::rotate(samples.begin(), samples.begin() + windowRotate, samples.end());
			for (int i = SUBSAMPLE - windowRotate; i < SUBSAMPLE; i++) {
				samples[i] = tailBuffer();
			}
			prevRes = currRes;
			currRes[0] = goertzel_mag(samples.size(), 1633, SAMPLE_RATE_LISTEN, samples);
			currRes[1] = goertzel_mag(samples.size(), 770, SAMPLE_RATE_LISTEN, samples);

			//check for downslope
			if (currRes[0] < prevRes[0] && currRes[1] < prevRes[1] && downSlope == false && currRes[1] > threshold&& currRes[0] > threshold) {
				downSlope = true;
				std::cout << "Downslope" << "\n"; //debugging
			}

			//check for upslope
			if (currRes[0] > prevRes[0] && currRes[1] > prevRes[1] && downSlope == true && currRes[1] > threshold&& currRes[0] > threshold) {
				std::cout << "Upslope" << "\n"; //debugging
				//here we check for peak
				while (prevRes < currRes && currRes[1] > threshold&& currRes[0] > threshold) {
					prevRes = currRes;
					currRes[0] = goertzel_mag(samples.size(), 1633, SAMPLE_RATE_LISTEN, samples);
					currRes[1] = goertzel_mag(samples.size(), 770, SAMPLE_RATE_LISTEN, samples);

				}
				std::cout << "peak found" << "\n"; //debugging

				//here we wait till start of next tone by updating our tail
				for (int i = 0; i < wait; i++) {
					tailBuffer();
				}
				std::cout << "into the while\n"; //debugging

				//here we update our window
				samples.clear(); 
				samples.resize(numSamples); 
				for (int i = 0; i < numSamples; i++) {
					samples[i] = tailBuffer();
				}

				//listen for end synchronize tone
				highFreq = findHighestFreq(numSamples, SAMPLE_RATE_LISTEN, samples);
				while (!(highFreq[1] == 1336.0f && highFreq[0] == 697.0f)) {
					for (int i = 0; i < numSamples; i++) {
						tailBuffer();
					}
					for (int i = 0; i < numSamples; i++) {
						samples[i] = tailBuffer();
					}
					highFreq = findHighestFreq(numSamples, SAMPLE_RATE_LISTEN, samples);
				}
				//debugging
				for (int i = 0; i < 2; i++) {
					std::cout << highFreq[i] << "\n";
				}

				return true;
			}
		}
	}
}

//--------------------------------------------------------------------------------------
std::vector<int> PhysicalLayer::listenToSound() {
	int numSamples = 44100 / 4; //expected tone length in samples
	std::vector<float> samples;
	samples.resize(numSamples);

	std::vector<float> freq;
	freq.resize(2);

	std::array<int, 4> results;
	std::vector<int> notBool;

	int DTMFfreq[] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	int soundWidth = 44100;

	float mag = 0.0f;
	float mag1 = 0.0f;

	unsigned short nippleLength;

	float threshold = 150.0f; //tested threshold at 35 cm

	std::cout << "we have the highground\n"; //debugging

	//wait for pause
	for (int i = 0; i < numSamples + numSamples/2; i++) {
		tailBuffer();
	}

	int k = 0;
	std::cout << "Check nipple\n";
	// check nibble size on incomming frame
	while (k < 2) {
		for (int i = 0; i < numSamples; i++) {
			samples[i] = tailBuffer();
		}

		freq = findHighestFreq(samples.size(), SAMPLE_RATE_LISTEN, samples);
		mag = goertzel_mag(numSamples, freq[0], SAMPLE_RATE_LISTEN, samples);
		mag1 = goertzel_mag(numSamples, freq[1], SAMPLE_RATE_LISTEN, samples);

		if (mag > threshold && mag1 > threshold) {
			freqToNipples(freq, results);

			if (k == 0) {
				nippleLength = results[0];
				for (int i = 1; i < results.size(); i++) {
					nippleLength = nippleLength << 1;
					nippleLength = nippleLength | results[i];
				}
			}
			if (k == 1) {
				for (int i = 0; i < results.size(); i++) {
					nippleLength = nippleLength << 1;
					nippleLength = nippleLength | results[i];
				}
			}
			k++;
			mag = 0.0f;
			mag1 = 0.0f;
		}
	}

	if(nippleLength > 36){
		nippleLength = 36;
	}

	std::cout << "frame length in nipples: " << nippleLength << "\n"; //debugging

	for (int j = 0; j < nippleLength ; j++) {
		//update buffer
		for (int i = 0; i < numSamples; i++) {
			samples[i] = tailBuffer();
		}

		freq = findHighestFreq(samples.size(), SAMPLE_RATE_LISTEN, samples);
		mag = goertzel_mag(numSamples, freq[0], SAMPLE_RATE_LISTEN, samples);
		mag1 = goertzel_mag(numSamples, freq[1], SAMPLE_RATE_LISTEN, samples);

		if (mag > threshold && mag1 > threshold) {
			freq = findHighestFreq(samples.size(), SAMPLE_RATE_LISTEN, samples);

			freqToNipples(freq, results);

			std::cout << "nipple: "; //debugging

			//pushing nibbles into vector
			for (int i = 0; i < results.size(); i++) {
				std::cout << results[i];
				notBool.push_back(results[i]);
			}

			mag = 0.0f;
			mag1 = 0.0f;
			std::cout << "\n"; // debugging
		}
	}

	//debugging
	for (int i = 0; i < notBool.size(); i++) {
		std::cout << notBool[i];
	}
	std::cout << std::endl;

	return notBool;
}



//--------------------------------------------------------------------------------------
//finds the most present DTMF tone
std::vector<float> PhysicalLayer::findHighestFreq(int numSamples, unsigned int SAMPLING_RATE, std::vector<float> data) {
	std::vector<float> result;
	int DTMFfreq[] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	float magnitudes[8], magnitudes2[8];

	for (int i = 0; i < 8; i++) {
		magnitudes[i] = goertzel_mag(numSamples, DTMFfreq[i], SAMPLING_RATE, data);
		magnitudes2[i] = goertzel_mag(numSamples, DTMFfreq[i], SAMPLING_RATE, data);
	}

	std::sort(magnitudes, magnitudes + 8);

	float max1, max2;

	max1 = magnitudes[6];
	max2 = magnitudes[7];
	/*
		Here we find the positions of the highest magnitudes */
	int pos1, pos2;
	for (int i = 0; i < 8; i++) {
		if (magnitudes2[i] == max1) {
			pos1 = i;
		}
		if (magnitudes2[i] == max2) {
			pos2 = i;
		}
	}

	//Here we make a sorted array of the corresponding DTMF frequency from the position of the highest magnitudes
	float sortFreq[] = { DTMFfreq[pos2], DTMFfreq[pos1] };
	std::sort(sortFreq, sortFreq + 2);

	result.insert(result.begin(), std::begin(sortFreq), std::end(sortFreq));

	return result;
}

//finds the magnitudes of a requested frequency
float PhysicalLayer::goertzel_mag(int numSamples, int TARGET_FREQ, unsigned int SAMPLING_RATE, std::vector<float> data) {
	int k, i;
	float floatnumSamples;
	float omega, sine, cosine, coeff, q0, q1, q2, magnitude, real, imag;

	float scalingFactor = numSamples / 2.0;

	floatnumSamples = (float)numSamples;
	k = (int)(0.5 + ((floatnumSamples * TARGET_FREQ) / SAMPLING_RATE));
	omega = (2.0 * M_PI * k) / floatnumSamples;
	sine = sin(omega);
	cosine = cos(omega);
	coeff = 2.0 * cosine;
	q0 = 0;
	q1 = 0;
	q2 = 0;

	for (i = 0; i < numSamples; i++) {
		q0 = coeff * q1 - q2 + data[i];
		q2 = q1;
		q1 = q0;
	}
	real = (q1 - q2 * cosine) / scalingFactor;
	imag = (q2 * sine) / scalingFactor;

	magnitude = sqrtf(pow(real, 2) + pow(imag, 2));

	return magnitude;
}

//--------------------------------------------------------------------------------------
//debugging
int PhysicalLayer::debug() {
	int DTMFfreq[] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	int freq = 697;
	float mag = 0.0f;
	std::vector<float> samples;
	samples.resize(22050);
	int windowRotate = 300;

	sf::sleep(sf::seconds(2));
	std::cout << "go" << std::endl;

	std::ofstream outputFile("goertzel_mag_test.csv");
	for (int j = 0; j < SUBSAMPLE; j++) {
		samples[j] = tailBuffer();
	}

	for (int j = 0; j < 1000; j++) {

		std::rotate(samples.begin(), samples.begin() + windowRotate, samples.end());
		for (int i = SUBSAMPLE - windowRotate; i < SUBSAMPLE; i++) {
			samples[i] = tailBuffer();
		}

		mag = PhysicalLayer::goertzel_mag(samples.size(), freq, SAMPLE_RATE_LISTEN, samples);
		outputFile << mag << ",";
	}
	outputFile.close();

	return 0;
}