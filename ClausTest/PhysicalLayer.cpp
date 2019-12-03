#include "PhysicalLayer.h"
#include <iostream>
#include <array>
#include <bitset>
#include <chrono>     
#include <ctime> 
#include <SFML/Audio.hpp>

#define M_PI 3.1415926535
#define SUBSAMPLE 8820



//bool PhysicalLayer::readyToSend() {
//	if (sending || receiving) {
//		return false;
//	}
//	else {
//		return true;
//	}
//}

//--------------------------------------------------------------------------------------
//-------------------------------------constructors-------------------------------------
//--------------------------------------------------------------------------------------
PhysicalLayer::PhysicalLayer() {
	bufferCount = 0x1FF;
	setProcessingInterval(sf::milliseconds(100));//default er 100
	buffer[0x1FF] = { 0 };
	head = buffer;
	listen = true;
}


PhysicalLayer::~PhysicalLayer() {
	std::cout << "hejsa" << std::endl;
	stop();
	listen = false;
	sf::sleep(sf::milliseconds(20));
	std::cout << "DESTRUCTOID" << std::endl;
}
//--------------------------------------------------------------------------------------
//---------------------------------------Receiver---------------------------------------
//--------------------------------------------------------------------------------------

bool PhysicalLayer::onProcessSamples(const int16_t* samples, std::size_t sampleCount) {
	for (short i = 0; i < sampleCount; i++) {
		//assign value to head of buffer
		*(head++) = *(samples + i);
		//reset head if end is reached
		if (head > buffer + bufferCount)
			head = buffer;
	}

	return listen;
}

float PhysicalLayer::tailBuffer() {
	//reset tail if end is reached
	if (PhysicalLayer::tail > buffer + bufferCount || tail < buffer)
		tail = &buffer[0];

	//wait til head is a-head
	while (tail >= head)
		;
	std::cout << "\ntail: " << tail << "\n";
	std::cout << "bufferEnd: " << buffer + bufferCount << "\n";
	try
	{
		std::cout << "\ntail: " << tail << "\n";
		std::cout << "bufferStart: " << buffer << "\n";
		std::cout << "bufferEnd: " << buffer + bufferCount << "\n";
		return (*tail++);
	}
	catch (...)
	{
		std::cout << "out of range";
		return 1;
	}

}

bool PhysicalLayer::listenStartBit(int sleepTime) {

	std::cout << "into the void" << std::endl;
	while (true) {
		tailBuffer();
	}

	std::cout << "out of the void" << std::endl;
	return true;
}
