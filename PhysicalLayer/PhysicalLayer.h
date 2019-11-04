#pragma once
#include <thread>
#include <vector>
#include <algorithm> 
#include <SFML/Audio.hpp>


class PhysicalLayer
{
public:
	////Sender
	//void playSound(int bitString);
	//bool readyToSend();

	////Receiver
	//bool readyToReceive();
	//bool listenStartBit();
	//int listenToSound();
	void static sendBitString(int bitString);


private:
	//	//Receiver methods
	//	float goertzel_mag(int numSamples, int TARGET_FREQ, unsigned int SAMPLING_RATE, const sf::Int16* data);
	//	float* findHighestFreq(int numSamples, unsigned int SAMPLING_RATE, const sf::Int16* data);
	//
	//	//Receiver & Sender variables
	//	std::vector<double> EN = { 1209, 697 };
	//	std::vector<double> TO = { 1336, 697 };
	//	std::vector<double> TRE = { 1477, 697 };
	//	std::vector<double> A = { 1633, 697 };
	//	std::vector<double> FIRE = { 1209, 770 };
	//	std::vector<double> FEM = { 1336, 770 };
	//	std::vector<double> SEKS = { 1477, 770 };
	//	std::vector<double> B = { 1633, 770 };
	//	std::vector<double> SYV = { 1209, 852 };
	//	std::vector<double> OTTE = { 1336, 852 };
	//	std::vector<double> NI = { 1477, 852 };
	//	std::vector<double> C = { 1633, 852 };
	//	std::vector<double> STJERNE = { 1209, 941 };
	//	std::vector<double> NUL = { 1336, 941 };
	//	std::vector<double> HAVELAAGE = { 1447, 941 };
	//	std::vector<double> D = { 1633, 941 };
	//
	//	bool sending, receiving;
	//
	//	sf::SoundBufferRecorder recorder;
};

