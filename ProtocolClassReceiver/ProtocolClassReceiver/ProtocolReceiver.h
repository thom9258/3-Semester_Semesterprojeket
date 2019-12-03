#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>




class ProtocolReceiver
{
	std::vector<int> vec;
public:

	int readFrom;
	int readTo;
	ProtocolReceiver(std::vector<int> input) : FullFrame(input) {};


	int getVectorLength (std::vector<int> v1) {
		std::vector<int> numbersOfLetters;
		for (int i = 0; i < 4; i++) {

			numbersOfLetters.push_back(v1[i]);
		}
		int n = convertBinaryToDecimal(numbersOfLetters);
		return n;

	}
	std::vector <int> getVectorBitData(std::vector<int> v1, int readFrom, int readTo) {

		std::vector <int> vectorBits;
		for (int i = readFrom; i < readTo; i++) {

			vectorBits.push_back(v1.at(i));
		};


		return vectorBits;
	};




	int convertBinaryToDecimal(std::vector <int> v1)
	{
		int n = v1.at(0) * 1 + v1.at(1) * 2 + v1.at(2) * 4 + v1.at(3) * 8;


		return n;
	}




	//check crc
    

	//RecNumbering

	//RecFlagDetermine
	int getFlagbits(std::vector<int> vec) {
		//getVectorBitData(std::vector<int> inputVector, 0, 4)
		if(vec[4]=1){
			sf = 1;
		};
		if (vec[3] = 1) {
			uligeFlag = 1;
		};

	}
	//ConvertData


private:

	std::vector<int> FullFrame;
	int sf;
	int uligeFlag;
    std::string final;
};
