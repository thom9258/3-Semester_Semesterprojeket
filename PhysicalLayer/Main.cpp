#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>  
#include "PhysicalLayer.h"
#define M_PI 3.1415926535

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
	/*std::vector<int> fuckmikkelogthomas{ 0,0,0,0,1,1,1,0,1,0,1,0 };
	PhysicalLayer::sendBitString(fuckmikkelogthomas);*/
	//while(true)

	// Usage
	PhysicalLayer cat;
	cat.start();

	cat.listenStartBit();
	cat.stop();
	return 0;
}
