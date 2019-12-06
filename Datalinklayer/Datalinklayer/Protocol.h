#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "Binary.h"

std::vector<int> ACK = { 1,1,1,1,1,0,1,1,1,0,1,1 };
std::vector<int> NACK = { 1,0,0,0,1,1,1,0,1,0,0,0 };
std::vector<int> ACKReq = { 1,0,1,0,1,1,0,1,0,0,1,0 };

std::vector<int> previousmessage;
std::vector<int> previousControlFrame = {1,0,0,0,1,1,1,0,1,0,0,0};

void setPreviousControlFrame(std::vector<int> input){
    previousControlFrame = input;
}

void setPrevious(std::vector<int> input){
    previousmessage = input;
}


std::string fullMessageString;

void addToFullMessage(std::string input) {
	fullMessageString += input;
}
void resetFullMessage(void) {
	fullMessageString = "";
}




class Protokol {

public:

    Protokol(std::string input) : fullsentence(input){};
    
    //Get the first 16 letters
        std::string getF16()
        {
            return first_16;
        }
    
    //Get the full sentence(the first 16 will be erased each time)
    
        std::string getFS()
        {
            return fullsentence;
        };
    
    // Divides the sentence, and saves the first 16 characters in one variable.
    std::string divider()
    {
        
        if (fullsentence.length() > 16) {
            first_16 = fullsentence.substr(0,16);
            fullsentence = fullsentence.erase(0,16);
            framecounterSender++;
            return first_16;
        }
        else{
            first_16 = fullsentence;
            fullsentence.clear();
            framecounterSender++;
            return first_16;
            
        }
    };
    
    int numberingSender()
       {
           NumOfChar = first_16.length();
           return NumOfChar;
       };
       
       void getNumbering()
       {
           std::cout << NumOfChar;
       }
    
    void flagDetermineSender()
    {
        //Slut flag tjek
        if(fullsentence.length() == 0){
            sfSender = 1;
        }
        else{
            sfSender = 0;
        }
        if (framecounterSender % 2 == 0) {
            ulSender = 0;
        }
        else {
            ulSender = 1;
        }
        
    }
    
    int getFramecounter()
    {
        return framecounterSender;
    };
    
    int getSF()
    {
        return sfSender;
    };
    
    int getUL()
    {
        return ulSender;
    }
    
    std::string SenderCRC(std::string message)
    {
        
        std::string CRC = "100011101";

    std::string encresult="";

        encresult += message;

        int n = CRC.length();

        for(int i = 1; i<=n-1; i++){
            encresult += '0';
        }
        for(int i = 0; i <= encresult.length()-n; ){
            for (int k=0; k<n; k++)
                encresult[i+k] = encresult[i+k]==CRC[k]? '0' : '1';
                for( ; i < encresult.length() && encresult[i] != '1'; i++);

        }

        std::string final = message + encresult.substr(encresult.length()-n+1);
        return final;
    }
    
    
    
    
    
    
    
    //EVERYTHING FOR VECTOR FUNCTION
    
    
    
    
    Protokol(std::vector<int> input) : FullFrame(input) {};
    
    int numberingReceiver(std::vector<int> input)
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
    
    void flagdetermineReceiver(){
        if (FullFrame[6] == 1) {
            ulReceiver = 1;
        }
        
        else {
            ulReceiver = 0;
        }
        
        if (FullFrame[7] == 1) {
            sfReceiver = 1;
        }
        
        else{
            sfReceiver = 0;
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
    //        for (int i = pol.size() - 1; i > 0; i--) { resultVec.push_back(0); }

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
    
    int getsfReceiver(){
        return sfReceiver;
    }

    int getulReceiver(){
        return ulReceiver;
    }
    
    int getframecounter(){
        framecounterReceiver++;
        return framecounterReceiver;
    }
    
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
                Binary currBin(currFrame);
                result = result + currBin.BinToChar();
            }
        }
        std::replace(result.begin(), result.end(),'_', ' ');
        return result;
    }
    
    
	//Function that checks every frame for errors. 
	bool errorCheck(Protokol p2)
	{
		bool final = true;
		if ((p2.getData() == ACK) || (p2.getData() == NACK) || (p2.getData() == ACKReq)) {
			if (p2.CheckCRC() == true) {
				std::cout << "CRC check is true" << std::endl;
				// if true, keep going
			}
			else {
				return final = false;
			}
		}
		else {
			if (p2.CheckCRC() == true) {
				std::cout << "CRC check is true" << std::endl;
				// if true, keep going
			}
			else {
				std::cout << "CRC check is false" << std::endl;
				return final = false;
			}
			int a = p2.numberingReceiver(p2.getData());
			int b = p2.databytesDetermine().size();
			if (a * 8 == b) {
				std::cout << "Number of bytes is correct" << std::endl;
			}
			else {
				std::cout << "Number of bytes is incorrect" << std::endl;
				return final = false;
			}
			
			if (p2.getframecounter() % 2 != p2.getulReceiver()) {
				std::cout << "Correct even/odd frame received" << std::endl;
			}
			else {
				std::cout << "Not the even/odd frame I expected" << std::endl;
				return final = false;
			}
			return final;
		}
		return final;
	}
	
    
    //hej
  
private:
    //FOR STRING FUNCTION
    std::string fullsentence;
    std::string first_16;
    //lige = 0, ulige = 1
    int framecounterSender = 0;
    int NumOfChar;
    int sfSender = 0, ulSender = 0;
    
    
    
    
    //FOR VECTOR FUNCTION
    std::vector<int> FullFrame;
    int numbering;
    int sfReceiver = 0, ulReceiver = 0;
    int framecounterReceiver = 1;


};




