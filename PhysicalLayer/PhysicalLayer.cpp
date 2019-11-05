#include "PhysicalLayer.h"
#include <iostream>;
#include <array>
#include <bitset>
#define M_PI 3.1415926535

//Sender
//void PhysicalLayer::playSound(int bitString) {
//	sending = true;
//}
//
//bool PhysicalLayer::readyToSend() {
//	if (sending || receiving) {
//		return false;
//	}
//	else {
//		return true;
//	}
//}

//Receiver
void PhysicalLayer::sendBitString(int bitString) {
	int nipple = bitString;
	int k;
	std::array<double, 2> arr;
	std::vector<std::array<double, 2>> TUNES;
	int i = 0;
	while (!nipple == 0) {
		k = nipple & 0b1111;
		std::cout << "AND with 0b1111: " << std::bitset<4>(k) << std::endl;
		std::cout << "AND with 0b0011: " << std::bitset<4>(k & 0b0011) << std::endl;
		std::cout << "AND with 0b1100: " << std::bitset<4>(k & 0b1100) << std::endl;

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
		nipple = nipple >> 4;
		i++;
	}
	/*std::cout << "playing sound " << TUNES[0][0] << " and " << TUNES[0][1] << "\n";
	std::cout << "playing sound " << TUNES[1][0] << " and " << TUNES[1][1] << "\n";
	std::cout << i << std::endl;*/


	//PLAY SOUND

	const unsigned toneCount = TUNES.size();

	float BPS = 1;
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

	//if (!FILE.openFromFile("DTMF.wave", SAMPLES, 1))
	//	std::cout << "could not save to file\n";
	//else
	//	FILE.write(raw, SAMPLES);
}
//
//bool PhysicalLayer::listenStartBit() {
//	int sleepTime = 1;
//
//	recorder.start();
//	sf::sleep(sf::seconds(sleepTime));
//	recorder.stop();
//
//	const sf::SoundBuffer& buffer = recorder.getBuffer();
//	unsigned int SAMPLE_RATE = recorder.getSampleRate();
//	const sf::Int16* samples = buffer.getSamples();
//	std::size_t count = buffer.getSampleCount();
//
//	float* p;
//	int frequencies[8];
//
//	p = PhysicalLayer::findHighestFreq(count, SAMPLE_RATE, samples);
//	for (int i = 0; i < 8; i++) {
//		frequencies[i] = *(p + i);
//	}
//	if (frequencies[7] == 440) {
//		return false;
//	}
//	else {
//		return true;
//	}
//}
//
//int PhysicalLayer::listenToSound() {
//	receiving = true;
//	int sleepTime = 20;
//
//	
//	while (!PhysicalLayer::listenStartBit());
//	
//	//Check if recorder is available
//	if (!sf::SoundBufferRecorder::isAvailable()){
//		std::cerr << "Error: Recorder not available!" << std::endl;
//	}
//	else {
//		recorder.start();
//		sf::sleep(sf::seconds(sleepTime));
//		recorder.stop();
//	}
//}
//
////
//float* PhysicalLayer::findHighestFreq(int numSamples, unsigned int SAMPLING_RATE, const sf::Int16* data) {
//	const sf::SoundBuffer& buffer = recorder.getBuffer();
//	unsigned int SAMPLE_RATE = recorder.getSampleRate();
//	const sf::Int16* samples = buffer.getSamples();
//	std::size_t count = buffer.getSampleCount();
//
//	int DTMFfreq[] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
//	float magnitudes[8], magnitudes2[8];
//
//	for (int i = 0; i < 8; i++) {
//		magnitudes[i] = goertzel_mag(count, DTMFfreq[i], SAMPLE_RATE, samples);
//		magnitudes2[i] = goertzel_mag(count, DTMFfreq[i], SAMPLE_RATE, samples);
//	}
//
//	std::sort(magnitudes, magnitudes + 8);
//
//	//We only want the two highest magnitudes so here we define them as max1 and max2
//	float maxSortValues[8];
//	float max;
//	int pos;
//	for (int i = 0; i < 8; i++) {
//		max = magnitudes[i];
//		for (int j = 0; j < 8; j++) {
//			if (magnitudes2[j] == max) {
//				pos = j;
//			}
//		}
//		maxSortValues[i] = DTMFfreq[pos];
//	}
//
//	return maxSortValues;
//}
//
////Maybe delete????? Hvornår er vi klar til at modtage?
//bool PhysicalLayer::readyToReceive() {
//	if (sending || receiving) {
//		return false;
//	}
//	else {
//		return true;
//	}
//}
//
////
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

