#include "PhysicalLayer.h"
#include <iostream>
#include <array>
#include <bitset>
#include <chrono>     
#include <ctime> 
#include <SFML/Audio.hpp>

#define M_PI 3.1415926535
#define SUBSAMPLE 3600

//--------------------------------------------------------------------------------------
//----------------------------------------Sender----------------------------------------
//--------------------------------------------------------------------------------------

//bool PhysicalLayer::readyToSend() {
//	if (sending || receiving) {
//		return false;
//	}
//	else {
//		return true;
//	}
//}

PhysicalLayer::PhysicalLayer()
{
	bufferCount = 0;
	buffer[0xFFFF] = {0};
	listen = true;
}

PhysicalLayer::~PhysicalLayer() {
	stop();
	listen = false;
	sf::sleep(sf::milliseconds(20));
}
//--------------------------------------------------------------------------------------

void PhysicalLayer::sendBitString(std::vector<int> bitString, float BPS) {
	std::vector<int> nipples;
	for (int i = 0; i < bitString.size(); i+=4) {	
		int temp = 0;
		for (int j = 0; j < 4; j++) {
			temp = temp << 1;
			temp += bitString[j + i];
		}
		nipples.push_back(temp);
	}
	std::reverse(nipples.begin(), nipples.end());

	//for (int i = 0; i < nipples.size(); i++) {
	//	std::cout << std::bitset<4>(nipples[i]) << std::endl;
	//}

	//int nipple = bitString;
	int k;
	std::array<double, 2> arr;
	std::vector<std::array<double, 2>> TUNES;
	int i = 0;

	for (int i = 0; i < nipples.size(); i++) {
		k = nipples[i];
		switch (k & 0b0011) {
		case 0b0000:
			arr[0] = 1209;
			break;
		case 0b0001:
			arr[0] = 1336;
			break;
		case 0b0010:
			arr[0] = 1477;
			break;
		case 0b0011:
			arr[0] = 1633;
			break;
		}

		switch (k & 0b1100) {
		case 0b0000:
			arr[1] = 697;
			break;
		case 0b0100:
			arr[1] = 770;
			break;
		case 0b1000:
			arr[1] = 852;
			break;
		case 0b1100:
			arr[1] = 941;
			break;
		}

		TUNES.push_back(arr);
	}

	//PLAY SOUND
	const unsigned toneCount = TUNES.size();
	const unsigned SAMPLES = 44100;
	unsigned SAMPLE_RATE = (SAMPLES / toneCount) * BPS;
	int samplePerTone = SAMPLES / toneCount;

	unsigned AMPLITUDE = 5000;
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
			raw[i] = AMPLITUDE * sin(x * TWO_PI) + AMPLITUDE * sin(y * TWO_PI);
			x += TUNES[j][0] / SAMPLE_RATE;
			y += TUNES[j][1] / SAMPLE_RATE;

		}

		//load sound to bufffer

		std::cout << "playing sound " << TUNES[j][0] << " and " << TUNES[j][1] << "\n";

	}
	if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
		std::cerr << "Loading failed!" << std::endl;
	}

	//output sound
	Sound.setBuffer(Buffer);
	Sound.play();
	std::cout << "Spiller jeg?" << std::endl;
	sf::sleep(sf::seconds((toneCount / BPS)));

}

//--------------------------------------------------------------------------------------

void PhysicalLayer::sendStartBit(int startBit, float BPS) {
	//PLAY SOUND
	int k = startBit;
	std::array<double, 2> arr;
	std::vector<std::array<double, 2>> TUNES;
	switch (k & 0b0011) {
	case 0b0000:
		arr[0] = 1209;
		break;
	case 0b0001:
		arr[0] = 1336;
		break;
	case 0b0010:
		arr[0] = 1477;
		break;
	case 0b0011:
		arr[0] = 1633;
		break;
	}

	switch (k & 0b1100) {
	case 0b0000:
		arr[1] = 697;
		break;
	case 0b0100:
		arr[1] = 770;
		break;
	case 0b1000:
		arr[1] = 852;
		break;
	case 0b1100:
		arr[1] = 941;
		break;
	}
	TUNES.push_back(arr);

	const unsigned toneCount = TUNES.size();

	const unsigned SAMPLES = 44100;
	unsigned SAMPLE_RATE = (SAMPLES / toneCount) * BPS;
	int samplePerTone = SAMPLES / toneCount;

	unsigned AMPLITUDE = 5000;
	sf::Int16 raw[SAMPLES];
	double incrementX;
	double incrementY;
	double x = 0, y = 0;		//sine funktion variable  
	sf::SoundBuffer Buffer;		//define sound buffer
	sf::Sound Sound;			//define Sound output
	//sf::OutputSoundFile FILE;	//define file
	x = 0;
	y = 0;
	const double TWO_PI = 6.28318;
	for (int j = 0; j < toneCount; j++)
	{
		unsigned start = (samplePerTone)*j;
		unsigned slut = (j + 1) * (samplePerTone);

		//generate sine function
		for (unsigned i = start; i < slut; i++) { // loop for every sample
			raw[i] = AMPLITUDE * sin(x * TWO_PI) + AMPLITUDE * sin(y * TWO_PI);
			x += TUNES[j][0] / SAMPLE_RATE;
			y += TUNES[j][1] / SAMPLE_RATE;

		}

		//load sound to bufffer

		std::cout << "playing sound " << TUNES[j][0] << " and " << TUNES[j][1] << "\n";

	}
	if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
		std::cerr << "Loading failed!" << std::endl;
	}

	//output sound
	Sound.setBuffer(Buffer);
	Sound.play();
	std::cout << "Spiller jeg?" << std::endl;
	sf::sleep(sf::seconds((toneCount / BPS)));
};


//--------------------------------------------------------------------------------------
//---------------------------------------Receiver---------------------------------------
//--------------------------------------------------------------------------------------

bool PhysicalLayer::onProcessSamples(const int16_t* samples, std::size_t sampleCount)
{
	for (unsigned short i = 0; i < sampleCount; i++, bufferCount++) 
		PhysicalLayer::buffer[bufferCount] = *(samples + i);
	return listen;
}

bool PhysicalLayer::listenStartBit(int sleepTime) {
	bool previousResult = false;
	float* p;
	int frequencies[2];
	std::vector<float> samples;
	unsigned short tailBuffer = 0;
	while (true) {
		while (tailBuffer + SUBSAMPLE < bufferCount)
			;
		for (int i = 0; i < SUBSAMPLE; i++, tailBuffer++) {
			samples.push_back(buffer[tailBuffer]);
		}
		samples = PhysicalLayer::findHighestFreq(SUBSAMPLE, 44100, samples);
		for (int i = 0; i < 2; i++) {
			frequencies[i] = samples[i];
		}
		samples.clear();
		std::cout << frequencies[1] << "  " << frequencies[0] << "\n";
		if (frequencies[0] == 697 && frequencies[1] == 1209 && previousResult) {
			std::cout << "true" << std::endl;
			return true;
		}
		else if (frequencies[0] == 697 && frequencies[1] == 1209)
			previousResult = true;
		else
			previousResult = false;
	}
	return true;
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

float* PhysicalLayer::findHighestFreq(std::size_t numSamples, unsigned int SAMPLING_RATE, const sf::Int16* data) {

	int DTMFfreq[] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	float magnitudes[8], magnitudes2[8];

	//std::vector<float> data;
	//for (int i = 0; i < 689; i++) {
	//	for (int j = 0; j < 44100 / 4; j++) {
	//		data[i] = samples[j];
	//	}
	//}

	for (int i = 0; i < 8; i++) {
		magnitudes[i] = goertzel_mag(numSamples, DTMFfreq[i], SAMPLING_RATE, data);
		magnitudes2[i] = goertzel_mag(numSamples, DTMFfreq[i], SAMPLING_RATE, data);
	}

	std::sort(magnitudes, magnitudes + 8);

	float max1, max2;
	max1 = magnitudes[6];
	max2 = magnitudes[7];

	//Here we find the positions of the highest magnitudes 
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

	return sortFreq;
}

std::vector<float> PhysicalLayer::findHighestFreq(int numSamples, unsigned int SAMPLING_RATE, std::vector<float> data) {
	std::vector<float> result;
	int DTMFfreq[] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	float magnitudes[8], magnitudes2[8];

	//std::vector<float> data;
	//for (int i = 0; i < 689; i++) {
	//	for (int j = 0; j < 44100 / 4; j++) {
	//		data[i] = samples[j];
	//	}
	//}

	for (int i = 0; i < 8; i++) {
		magnitudes[i] = goertzel_mag(numSamples, DTMFfreq[i], SAMPLING_RATE, data);
		magnitudes2[i] = goertzel_mag(numSamples, DTMFfreq[i], SAMPLING_RATE, data);
	}

	std::sort(magnitudes, magnitudes + 8);

	float max1, max2;
	max1 = magnitudes[6];
	max2 = magnitudes[7];

	//Here we find the positions of the highest magnitudes 
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

float PhysicalLayer::goertzel_mag(int numSamples, int TARGET_FREQ, unsigned int SAMPLING_RATE, const sf::Int16* data) {
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