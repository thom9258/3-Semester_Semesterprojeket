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
	std::vector<int> bitstring = { 0, 0, 0, 0, 1, 1, 0, 0};

	


	//PhysicalLayer::sendStartBit(0b0000);
	std::vector<int> fuckmikkelogthomas{ 0,0,0,0,1,1,1,0,1,0,1,0 };
	PhysicalLayer::sendBitString(fuckmikkelogthomas);

	PhysicalLayer::listenStartBit();
	return 0;
}
