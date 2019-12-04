#pragma once
#include <thread>
#include <vector>
#include <algorithm> 
#include <iostream>
#include <SFML/Audio.hpp>


class PhysicalLayer : public sf::SoundRecorder
{
public:
	PhysicalLayer();
	~PhysicalLayer();

	float tailBuffer();


	bool listenStartBit(int sleepTime = 1000);


	//inheretance fra SFML 
	virtual bool OnStart() {return true; }

	virtual bool onProcessSamples(const int16_t* samples, std::size_t sampleCount);

	virtual void OnStop() {}


protected:
	unsigned int bufferCount;
	float buffer[0x1FF];
	float* tail;
	float* head;
	bool listen;
};
