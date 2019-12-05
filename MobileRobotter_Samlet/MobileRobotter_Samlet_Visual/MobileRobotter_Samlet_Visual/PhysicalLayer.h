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

	//Sender
	void static sendBitString(std::vector<int> bitString, float BPS = 4);
	void static sendStartBit(int startBit = 0b0111, int count = 3, float BPM = 2);
	void static sendNippleCount(std::vector<int> bitString, float BPS = 4);


	//Receiver
	bool listenStartBit(int sleepTime = 1000);
	std::vector<int> listenToSound();


	//inheritance fra SFML 
	virtual bool OnStart() { return true; }

	virtual bool onProcessSamples(const int16_t* samples, std::size_t sampleCount);

	virtual void OnStop(){}

	int debug();
	

private:
	std::size_t count;
	unsigned const SAMPLE_RATE = 44100;

	//Receiver methods
	float static goertzel_mag(int numSamples, int TARGET_FREQ, unsigned int SAMPLING_RATE, std::vector<float> data); //gør den compatibel med vector

	std::vector<float> static findHighestFreq(int numSamples, unsigned int SAMPLING_RATE, std::vector<float> data); //uhm... ved ikke hvorfor den ovenover har de argumenter så lave min egen
	
protected:
	std::array<float, 0xFFFF> buffer;
	int buffersize;
	bool listen;
	int head, tail;
};

