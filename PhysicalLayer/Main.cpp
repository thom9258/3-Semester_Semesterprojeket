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

	PhysicalLayer::sendBitString(0b1001'0000'1001'0000);


	return 0;
}
