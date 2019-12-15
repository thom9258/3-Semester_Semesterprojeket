#pragma once
#include <thread>
#include <vector>
#include <algorithm> 
#include <iostream>
#include <SFML/Audio.hpp>
#include <array>


class PhysicalLayer : public sf::SoundRecorder
{
public:
	PhysicalLayer();
	~PhysicalLayer();
	float tailBuffer();

	void transmit(std::vector<int> fraDataLink);

	//Sender
	//bool static readyToSend();
	void static sendBitString(std::vector<int> bitString, float BPS = 4);
	void static sendStartBit(int startBit = 0b0111, int count = 3, float BPM = 2);
	void static sendNippleCount(std::vector<int> bitString, float BPS = 4);


	////Receiver
	//bool readyToReceive();
	bool listenStartBit(int sleepTime = 1000);
	std::vector<int> listenToSound();
	//std::array<int, 4> listenToSound();
	
	
	//std::vector<int> dataToDataLink();

	//inheritance fra SFML 
	virtual bool OnStart() { return true; }

	virtual bool onProcessSamples(const int16_t* samples, std::size_t sampleCount);

	virtual void OnStop(){}



	int debug();
	

private:
	std::size_t count;
	unsigned const SAMPLE_RATE = 44100;

	//bool sending, receiving;
	//Receiver methods
	//float static goertzel_mag(int numSamples, int TARGET_FREQ, unsigned int SAMPLING_RATE, const sf::Int16* data);
	float static goertzel_mag(int numSamples, int TARGET_FREQ, unsigned int SAMPLING_RATE, std::vector<float> data); //gør den compatibel med vector

	//float static* findHighestFreq(std::size_t numSamples, unsigned int SAMPLING_RATE, const sf::Int16* data);
	std::vector<float> static findHighestFreq(int numSamples, unsigned int SAMPLING_RATE, std::vector<float> data); //uhm... ved ikke hvorfor den ovenover har de argumenter så lave min egen
	
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

protected:
	std::array<float, 0xFFFF> buffer;
	int buffersize;
	bool listen;
	int head, tail;
};

