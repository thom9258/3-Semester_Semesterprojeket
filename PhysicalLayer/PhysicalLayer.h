#pragma once
#include <thread>
#include <vector>
#include <algorithm> 
#include <SFML/Audio.hpp>


class PhysicalLayer
{
public:
	//Sender
	//bool static readyToSend();
	void static sendBitString(std::vector<int> bitString);
	void static sendStartBit(int startBit);


	////Receiver
	//bool readyToReceive();
	bool static listenStartBit();
	int static listenToSound();


private:
	std::size_t count;
	unsigned const SAMPLE_RATE = 44100;

	//bool sending, receiving;
	//	//Receiver methods
	float static goertzel_mag(int numSamples, int TARGET_FREQ, unsigned int SAMPLING_RATE, const sf::Int16* data);
	float static* findHighestFreq(int numSamples, unsigned int SAMPLING_RATE, const sf::Int16* data, sf::SoundBufferRecorder& buffer);
	//
	//Receiver & Sender variables
	std::vector<double> EN = { 1209, 697 };
	std::vector<double> TO = { 1336, 697 };
	std::vector<double> TRE = { 1477, 697 };
	std::vector<double> A = { 1633, 697 };
	std::vector<double> FIRE = { 1209, 770 };
	std::vector<double> FEM = { 1336, 770 };
	std::vector<double> SEKS = { 1477, 770 };
	std::vector<double> B = { 1633, 770 };
	std::vector<double> SYV = { 1209, 852 };
	std::vector<double> OTTE = { 1336, 852 };
	std::vector<double> NI = { 1477, 852 };
	std::vector<double> C = { 1633, 852 };
	std::vector<double> STJERNE = { 1209, 941 };
	std::vector<double> NUL = { 1336, 941 };
	std::vector<double> HAVELAAGE = { 1447, 941 };
	std::vector<double> D = { 1633, 941 };
};

