#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "BinaryReceiver.h"


class ProtocolReceiver
{
public:
	ProtocolReceiver(std::vector<int> input) : FullFrame(input) {};
    
    int numberingRec(std::vector<int> input)
    {
        input = FullFrame;
        std::vector<int> firstfour;
        
        for(int i = 0; i < 4; i++)
        {
            firstfour.push_back(input[i]);
        }
        
        numbering = firstfour.at(0) * 8 + firstfour.at(1) * 4 + firstfour.at(2) * 2 + firstfour.at(3) * 1;


        return numbering+1;
        }
    
    void flagdetermine(){
        if (FullFrame.at(6) == 1) {
            ul = 1;
        }
        
        else {
            ul = 0;
        }
        
        if (FullFrame.at(7) == 1) {
            sf = 1;
        }
        
        else{
            sf = 0;
        }
    }
    
    std::vector<int> getData()
    {
        return FullFrame;
    }
    
	// returns true if the message is correct
	//input of function below
	//std::vector<int> mes
	bool CheckCRC()
	{
		// the polynomial used to calculate crc
		std::vector<int> pol = { 1, 0,0,0,1, 1,1,0,1 };
		std::vector<int> resultVec;
		// changed this from mes to fullframe
		resultVec = FullFrame;

		// might not be used
//		for (int i = pol.size() - 1; i > 0; i--) { resultVec.push_back(0); }

		// crc algorithm
		while (resultVec.size() > pol.size() - 1)
		{
			std::vector<int> newPol = pol;

			// make the polynomial the size of the message
			while (newPol.size() != resultVec.size()) { newPol.push_back(0); }

			// eor the polynomial with the message
			for (int i = 0; i < newPol.size(); i++) { resultVec[i] = resultVec[i] ^ newPol[i]; }

			// remove excess zeros from msb of message
			while (resultVec[0] == 0 && resultVec.size() != 1) { resultVec.erase(resultVec.begin()); }
		}

		// return true if the message is equals to 0 after the crc algorithm
		if (resultVec[0] == 0) {
			return true;
		}
		else {
			return false;
		}
	}

    
    int getsf(){
        return sf;
    }

    int getul(){
        return ul;
    }
    
    int getframecounter(){
        framecountervar++;
        return framecountervar;
    }
    
	void setACK(std::vector <int> inp) { ACK = inp; }


    std::vector<int> databytesDetermine()
    {
        FullFrame.erase(FullFrame.begin(), FullFrame.begin()+8);
        
        FullFrame.erase(FullFrame.end()-8, FullFrame.end());
        
        return FullFrame;
    }
    

	std::string returnMessage(void) 
	{
		std::vector<int> ff = FullFrame;
		std::vector<int> currFrame;
		std::string result;

		while (ff.size() != 0) 
		{
			for (int i = 0; i < 8; i++) 
			{
				currFrame.push_back(ff.at(0));
				ff.erase(ff.begin());
				BinaryRec currBin(currFrame);
				result = result + currBin.BinToChar();
			}
		}
		return result;
	}


private:
	std::vector<int> FullFrame;
	std::vector<int> ACK = {1,1,1,1};
	std::vector<int> NACK = {0,0,0,0};
	std::vector<int> ACKReq = {1,0,1,0};
    int numbering;
    int sf = 0, ul = 0;
    int framecountervar = 0;
};
