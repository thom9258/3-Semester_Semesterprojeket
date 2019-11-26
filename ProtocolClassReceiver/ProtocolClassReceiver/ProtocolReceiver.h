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
	std::vector <int> getVectorLength(vector<int> v1) {
		vector<int> numbersOfLetters;
		for (int i = 0; i < 4; i++) {

			numbersOfLetters.push_back(v1[i])
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




	int convertBinaryToDecimal(vector <int> v1)
	{
		int n = v1.at(0) * 1 + v1.at(1) * 2 + v1.at(2) * 4 + v1.at(3) * 8;


		return n;
	}




	//check crc
	std::string receiver(std::string senderCRC, std::string CRC)
    {
        for(int i=0; i<=senderCRC.length()-CRC.length(); ) {
            for(int k=0; k<CRC.length(); k++)
                senderCRC[i+k]=senderCRC[i+k]==CRC[k]? '0' : '1';
                for(; i < senderCRC.length() && senderCRC[i]!='1'; i++);
            }

        for( char i: senderCRC.substr(senderCRC.length()-CRC.length()+1) )
            if(i!='0'){
                std::string final = "ERRRROOROOROR";
                return final;
            }
        std::string final = "No error :)";
                return final;
    }

	//RecNumbering

	//RecFlagDetermine
	int ProtocolReceiver::getFlagbits(vector<int> vec getVectorBitData(std::vector<int> inputVector, 0, 4)) {
		if(vec[4]=1){
			sf = 1;
		};
		if (vec[3] = 1) {
			uligeFlag = 1;
		};

	}
	//ConvertData


private:
	std::vector <int> getVectorFlags(vector<int> v1);
	std::vector <int> getVectorLength(vector<int> v1);
	std::vector<int> FullFrame;
	int sf;
	int uligeFlag;
    std::string final;
};
