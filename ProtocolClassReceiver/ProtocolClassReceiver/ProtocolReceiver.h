#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>


vector <int> getVectorFlags(vector<int> v1);
vector <int> getVectorLength(vector<int> v1);
int convertBinaryToDecimal(vector <int> v1);
int readFrom;
int readTo;
class ProtocolReceiver
{
public:
	ProtocolReceiver(std::vector<int> input) : FullFrame(input) {};

	int convertBinaryToDecimal(std::vector <int> v1);
	int readFrom;
	int readTo;

	std::vector <int> getVectorBitData(std::vector<int> v1, int readFrom, int readTo) {

		std::vector <int> vectorBits;
		for (int i = readFrom; i < readTo; i++) {

			vectorBits.push_back(v1.at(i));
		};


		return vectorBits;
	};




	int convertBinaryToDecimal(vector <int> v1)
	{
		int n = v1.at(0) * 1 + v1.at(1) * 2 + v1.at(2) * 4 + v1.at(3) * 8;


		return n;
	}




	//check crc

	//RecNumbering

	//RecFlagDetermine

	//ConvertData

    
private:
	std::vector <int> getVectorFlags(vector<int> v1);
	std::vector <int> getVectorLength(vector<int> v1);
	std::vector<int> FullFrame;
};
