#include "PhysicalLayer.h"
#include <iostream>
#include <array>
#include <bitset>
#include <chrono>     
#include <ctime> 
#include <SFML/Audio.hpp>

#define M_PI 3.1415926535
#define SUBSAMPLE 5500
#define SAMPLE_RATE_LISTEN 44100

//--------------------------------------------------------------------------------------
//-------------------------------------constructors-------------------------------------
//--------------------------------------------------------------------------------------
PhysicalLayer::PhysicalLayer() {
	setProcessingInterval(sf::milliseconds(100));//default er 100
	listen = true;
	buffersize = 0xFF;
	int head = 0;
	int tail = 0;
}

//--------------------------------------------------------------------------------------

PhysicalLayer::~PhysicalLayer() {
	stop();
	listen = true;
	sf::sleep(sf::milliseconds(20));
	std::cout << "DESTRUCTOID" << std::endl;
}

//--------------------------------------------------------------------------------------
//----------------------------------Practical function----------------------------------
//--------------------------------------------------------------------------------------

//finding frequency from nipple and save frequency to given array 
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

//--------------------------------------------------------------------------------------

void playTune(std::vector<std::array<double, 2>> TUNES, float BPS = 1, unsigned int AMPLITUDE = 5000) {
	const unsigned toneCount = TUNES.size();
	const unsigned SAMPLES = 44100;
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
			double window = 0.5 * (1 - cos(2 * M_PI * i / (slut - start)));
			raw[i] = window * (AMPLITUDE * sin(x * TWO_PI) + AMPLITUDE * sin(y * TWO_PI));
			x += TUNES[j][0] / SAMPLE_RATE;
			y += TUNES[j][1] / SAMPLE_RATE;

		}

		//load sound to bufffer

		std::cout << "playing sound " << TUNES[j][0] << " and " << TUNES[j][1] << "\n";

	}
	if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
		std::cerr << "Loading failed!" << std::endl;
	}

	Sound.setBuffer(Buffer);
	Sound.play();
	sf::sleep(sf::seconds((toneCount / BPS)));
}


//--------------------------------------------------------------------------------------
//----------------------------------------Sender----------------------------------------
//--------------------------------------------------------------------------------------


void PhysicalLayer::sendBitString(std::vector<int> bitString, float BPS) {
	std::reverse(bitString.begin(), bitString.end());
	std::vector<int> nipples;
	for (int i = 0; i < bitString.size(); i+=4) {	
		int temp = 0;
		for (int j = 3; j >= 0; j--) {
			temp = temp << 1;
			temp += bitString[j + i];
		}
		nipples.push_back(temp);
	}
	std::reverse(nipples.begin(), nipples.end());

	int k;
	std::array<double, 2> arr;
	std::vector<std::array<double, 2>> TUNES;
	int i = 0;

	for (int i = 0; i < nipples.size(); i++) {
		nipplesToFreq(nipples[i],arr);
		TUNES.push_back(arr);
	}

	//output sound
	playTune(TUNES, BPS);
}

//--------------------------------------------------------------------------------------

void PhysicalLayer::sendStartBit(int startBit, int count, float BPM) {
	//PLAY SOUND
	int k = startBit;
	std::array<double, 2> arr;
	std::vector<std::array<double, 2>> TUNES;
	nipplesToFreq(k,arr);
	TUNES.push_back(arr);
	for (int i = 0; i < count; i++)
		playTune(TUNES, BPM);

	TUNES.clear();
	k = 0b0001;
	nipplesToFreq(k, arr);
	TUNES.push_back(arr);
	playTune(TUNES, BPM);
};



//--------------------------------------------------------------------------------------
//---------------------------------------Receiver---------------------------------------
//--------------------------------------------------------------------------------------

bool PhysicalLayer::onProcessSamples(const int16_t* samples, std::size_t sampleCount) {
	
	for (int i = 0; i < sampleCount; i++) {
		if (head + 1 >= buffersize)
			head = 0;
		buffer[head++] = ((*(samples + i)));
	}
	return listen;
}

float PhysicalLayer::tailBuffer() {
	while (tail + 2 > head && head - tail > 0 || ((tail + 1 == buffersize) && head < 2))
		;
	if (tail +1 >= buffersize)
		tail = 0;
	return buffer[tail++];
}

bool PhysicalLayer::listenStartBit(int sleepTime) {
	bool downSlope = false;

	std::array<float, 2> prevRes = { 0,0 };
	std::array<float, 2> currRes = { 0,0 };

	std::vector<float> currentResult;
	std::vector<float> prevResult;
	prevResult.resize(2);
	currentResult.resize(2);
	listen = true;
	int DTMFfreq[] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	std::array<float, 2> oneTone = { 1336, 697 };

	int frequencies[8];
	std::vector<float> zeroTone(1209, 697);
	std::vector<float> highFreq;
	std::vector<float> samples;
	samples.resize(SUBSAMPLE);

	highFreq.resize(8);

	int windowRotate = 250;
	float threshold = 5.0f;

	for (int i = 0; i < SUBSAMPLE; i++) {
		samples[i] = tailBuffer();
	}
	float mag;
	while (true) {
		std::rotate(samples.begin(), samples.begin() + windowRotate, samples.end());
		for (int i = SUBSAMPLE - windowRotate; i < SUBSAMPLE; i++) {
			samples[i] = tailBuffer();
		}
		for (int i = 0; i < 8; i++) {
			mag = goertzel_mag(samples.size(), DTMFfreq[i], SAMPLE_RATE_LISTEN, samples);
			if (mag > 1)
				std::cout << "freq: " << DTMFfreq[i] << " mag: " << mag << "\n";
		}
		
		//std::rotate(samples.begin(), samples.begin() + windowRotate, samples.end());
		//for (int i = SUBSAMPLE - windowRotate; i < SUBSAMPLE; i++) {
		//	samples[i] = tailBuffer();
		//}
		//prevRes = currRes;
		//currRes[0] = goertzel_mag(samples.size(), 1209, SAMPLE_RATE_LISTEN, samples);
		//currRes[1] = goertzel_mag(samples.size(), 697, SAMPLE_RATE_LISTEN, samples);

		//if (currRes[0] < prevRes[0] && currRes[1] < prevRes[1] && downSlope == false) {
		//	downSlope = true;
		//	std::cout << "Downslobe" << "\n";
		//}
		//if (currRes[0] > prevRes[0] && currRes[1] > prevRes[1] && downSlope == true) {
		//	std::cout << "Upslobe" << "\n";
		//	while (prevRes < currRes) {
		//		prevRes = currRes;
		//		currRes[0] = goertzel_mag(samples.size(), 1209, SAMPLE_RATE_LISTEN, samples);
		//		currRes[1] = goertzel_mag(samples.size(), 697, SAMPLE_RATE_LISTEN, samples);
		//	}
		//	std::cout << "peak found" << "\n";

		//	for (int i = 0; i < 66150; i++) {
		//		tailBuffer();
		//		
		//	}
		//	//std::rotate(samples.begin(), samples.begin() + windowRotate, samples.end());
		//	for (int i = 0; i < SUBSAMPLE; i++) {
		//		samples[i] = tailBuffer();
		//	}


		//	highFreq = findHighestFreq(SUBSAMPLE, SAMPLE_RATE_LISTEN, samples);
		//	

		//	while (highFreq[1] != 1336 && highFreq[0] != 697) {
		//		for (int i = 0; i < 66150; i++) {
		//			tailBuffer();
		//		}
		//		//std::rotate(samples.begin(), samples.begin() + windowRotate, samples.end());
		//		for (int i = 0; i < SUBSAMPLE; i++) {
		//			samples[i] = tailBuffer();
		//		}
		//		highFreq = findHighestFreq(SUBSAMPLE, SAMPLE_RATE_LISTEN, samples);
		//	}
		//	return true;

		//}
	
	}

}

//

//--------------------------------------------------------------------------------------

//int PhysicalLayer::listenToSound() {
//	sf::SoundBufferRecorder recorder;
//	std::vector<std::array<int, 2>> DTMFBuffer;
//	int sleepTime = 1;
//	
//	int j = 0;
//	while (j < 2) {
//		if (PhysicalLayer::listenStartBit() == true) {
//			std::cout << "Startbit recognized" << std::endl;
//			j++;
//		}
//	}
//	std::cout << "Data transmission started" << std::endl;
//
//	//Check if recorder is available
//	if (!sf::SoundBufferRecorder::isAvailable()) {
//		std::cerr << "Error: Recorder not available!" << std::endl;
//	}
//
//	std::array<int, 2> arr;
//	int i = 0;
//	while (i < 20) {
//		recorder.start();
//		sf::sleep(sf::seconds(sleepTime));
//		recorder.stop();
//
//		const sf::SoundBuffer& buffer = recorder.getBuffer();
//		unsigned int SAMPLE_RATE = recorder.getSampleRate();
//		const sf::Int16* samples = buffer.getSamples();
//		std::size_t count = buffer.getSampleCount();
//
//		float* p;
//		int frequencies[2];
//
//		p = PhysicalLayer::findHighestFreq(count, SAMPLE_RATE, samples);
//		for (int i = 0; i < 2; i++) {
//			frequencies[i] = *(p + i);
//		}
//		arr = { frequencies[0], frequencies[1] };
//		std::cout << frequencies[1] << "   " << frequencies[0] << std::endl;
//		DTMFBuffer.push_back(arr);
//		i++;
//	}	
//
//
//	return 0;
//	
//}

//--------------------------------------------------------------------------------------

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

//--------------------------------------------------------------------------------------

////Maybe delete????? Hvornår er vi klar til at modtage?
//bool PhysicalLayer::readyToReceive() {
//	if (sending || receiving) {
//		return false;
//	}
//	else {
//		return true;
//	}
//}

//--------------------------------------------------------------------------------------

//float PhysicalLayer::goertzel_mag(int numSamples, int TARGET_FREQ, unsigned int SAMPLING_RATE, const sf::Int16* data) {
//	int k, i;
//	float floatnumSamples;
//	float omega, sine, cosine, coeff, q0, q1, q2, magnitude, real, imag;
//
//	float scalingFactor = numSamples / 2.0;
//
//	floatnumSamples = (float)numSamples;
//	k = (int)(0.5 + ((floatnumSamples * TARGET_FREQ) / SAMPLING_RATE));
//	omega = (2.0 * M_PI * k) / floatnumSamples;
//	sine = sin(omega);
//	cosine = cos(omega);
//	coeff = 2.0 * cosine;
//	q0 = 0;
//	q1 = 0;
//	q2 = 0;
//
//	for (i = 0; i < numSamples; i++) {
//		q0 = coeff * q1 - q2 + data[i];
//		q2 = q1;
//		q1 = q0;
//	}
//	real = (q1 - q2 * cosine) / scalingFactor;
//	imag = (q2 * sine) / scalingFactor;
//
//	magnitude = sqrtf(pow(real, 2) + pow(imag, 2));
//
//	return magnitude;
//}

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