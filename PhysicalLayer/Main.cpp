#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>  
#include "PhysicalLayer.h"
#define M_PI 3.1415926535



//--------------convert longlong to vector of "boleans"--------------
std::vector<int> binaryToVector(unsigned long long bit, char bitCount) {
	std::vector<int> result;
	result.reserve(bitCount);
	unsigned int k = 0b1;
	for (int i = 0; i < bitCount; i++) {
		k = 1;
		k = bit & k;
		result.push_back(k);
		bit = bit >> 1;
	}
	std::reverse(result.begin(), result.end());
	return result;
}

int main() {


	PhysicalLayer cat;
	cat.start();
	cat.listenStartBit();
	cat.listenToSound();

	return 0;
}
