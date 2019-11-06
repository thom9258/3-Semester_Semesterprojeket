#include "PhysicalLayer.h"
#include <iostream>;
#include <array>
#include <bitset>
#include <chrono>
#define M_PI 3.1415926535

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

//--------------------------------------------------------------------------------------

void PhysicalLayer::sendBitString(std::vector<int> bitString, float BPS = 1) {
	std::vector<int> nipples;
	std::reverse(bitString.begin(), bitString.end());
	for (int i = 0; i < bitString.size(); i+=4) {	
		int temp = 0;
		for (int j = 0; j < 4; j++) {
			temp += bitString[j + i];
			temp = temp << 1;
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
			double muliple = 0.5 *(1 - cos(2 * M_PI * i / (slut - start)));
			raw[i] = muliple * AMPLITUDE * (sin(x * TWO_PI) + sin(y * TWO_PI));
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

void PhysicalLayer::sendStartBit(int startBit, float BPS = 1) {
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


bool PhysicalLayer::listenStartBit(int sleepTime = 2) {
	sf::SoundBufferRecorder recorder;

	//alt herfra
	int hi = 0;
	for (int i = 0; i < 101; i++)
	{
		auto t1 = std::chrono::high_resolution_clock::now();
		recorder.start();
		//sf::sleep(sf::seconds(sleepTime));
		recorder.stop();
		auto t2 = std::chrono::high_resolution_clock::now();
		std::cout << "test function took "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
			<< " milliseconds\n";
		if (hi < std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count())
			hi = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	}
	std::cout<< "hi is: " << hi << std::endl;
	const sf::SoundBuffer& buffer = recorder.getBuffer();
	unsigned int SAMPLE_RATE = recorder.getSampleRate();
	const sf::Int16* samples = buffer.getSamples();
	std::size_t count = buffer.getSampleCount();

	float* p;
	int frequencies[2];
	
	/*p = PhysicalLayer::findHighestFreq(count, SAMPLE_RATE, samples, recorder);
	for (int i = 0; i < 2; i++) {
		frequencies[i] = *(p + i);
	}
	std::cout << frequencies[0] << "  " << frequencies[1] << std::endl;

	if (frequencies[0] == 697 && frequencies[1] == 1209) {
		std::cout << "true" << std::endl;
		return true;
	}
	else {
		std::cout << "false" << std::endl;
		return false;
	}*/
	return false;
}

//--------------------------------------------------------------------------------------

//
//int PhysicalLayer::listenToSound() {
//	int sleepTime = 2;
//	
//	//while (!PhysicalLayer::listenStartBit());
//	
//	//Check if recorder is available
//	if (!sf::SoundBufferRecorder::isAvailable()){
//		std::cerr << "Error: Recorder not available!" << std::endl;
//	}
//	else {
//		recorder.start();
//		std::cout << "Tone start" << std::endl;
//		sf::sleep(sf::seconds(sleepTime));
//		std::cout << "Tone slut" << std::endl;
//		recorder.stop();
//		const sf::SoundBuffer& buffer = recorder.getBuffer();
//		count = buffer.getSampleCount();
//		for (int i = 0; count; i++) {
//			DTMFBuffer[i] = recoder.getBuffer()[i];
//		}
//		DTMFbuffer = recorder.getBuffer();
//	}
//}

//--------------------------------------------------------------------------------------

float* PhysicalLayer::findHighestFreq(int numSamples, unsigned int SAMPLING_RATE, const sf::Int16* data, sf::SoundBufferRecorder& recorder) {
	const sf::SoundBuffer& buffer = recorder.getBuffer();
	unsigned int SAMPLE_RATE = recorder.getSampleRate();
	const sf::Int16* samples = buffer.getSamples();
	std::size_t count = buffer.getSampleCount();

	int DTMFfreq[] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	float magnitudes[8], magnitudes2[8];

	for (int i = 0; i < 8; i++) {
		magnitudes[i] = goertzel_mag(count, DTMFfreq[i], SAMPLE_RATE, samples);
		magnitudes2[i] = goertzel_mag(count, DTMFfreq[i], SAMPLE_RATE, samples);
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

