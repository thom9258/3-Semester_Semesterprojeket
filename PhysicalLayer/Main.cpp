#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>  
#include "PhysicalLayer.h"
#define M_PI 3.1415926535



std::vector<int> binaryToVector(unsigned int bit, char bitCount) {
	std::vector<int> result;
	result.reserve(bitCount);
	unsigned char k = 0b1;
	for (int i = 0; i < bitCount; i++) {
		k = 1;
		k = bit & k;
		result.push_back(k);
		bit = bit>> 1;
	}
	return result;
}

int main() {

	/*std::thread t1(record);

	t1.join();*/
	//int i = 0;
	//while (i < 2) {
	//	if (PhysicalLayer::listenStartBit() == true) {
	//		i++;
	//	}
	//}

	//PhysicalLayer::listenToSound();

	//std::vector<int> fuckmikkelogthomas{0,0,1,1};
	//PhysicalLayer::sendBitString(fuckmikkelogthomas);
	//PhysicalLayer::sendStartBit(0b0000);
	std::vector<int> fuckmikkelogthomas = binaryToVector(0b0000'0001'0000'0001'0000'0001'0000'0001'0001, 28);
	//PhysicalLayer::sendBitString(fuckmikkelogthomas);
	//while(true)

	// Usage
	PhysicalLayer cat;
	cat.start();
	//cat.sendStartBit(0b0000);
	cat.listenStartBit();
	sf::sleep(sf::seconds(2));
	return 0;
}
