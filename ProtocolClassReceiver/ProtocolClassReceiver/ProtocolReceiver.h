#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

class ProtocolReceiver
{
public:
	ProtocolReceiver(std::vector<int> input) : FullFrame(input) {};

	std::string receiverCRC(std::vector<int> input)
    {
        std::string senderCRC;
        
        for(int i = 0; i < input.size(); i++)
        {
            if(input[i] == 1){
                senderCRC.push_back('1');
            }
            else{
                senderCRC.push_back('0');
            }
        }
        
        std::string CRC = "100000111";
        for(int i=0; i<=senderCRC.length()-CRC.length(); ) {
            for(int k=0; k<CRC.length(); k++)
                senderCRC[i+k]=senderCRC[i+k]==CRC[k]? '0' : '1';
                for(; i < senderCRC.length() && senderCRC[i]!='1'; i++);
            }

        for( char i: senderCRC.substr(senderCRC.length()-CRC.length()+1) )
            if(i!='0'){
                CRCcheck = 0;
                //0 means no error
            }
        CRCcheck = 1;
        //1 means error
    }
    
    int getCRC{
        return CRCcheck;
    }

	//RecNumbering

	//RecFlagDetermine

	//ConvertData

    
private:
	std::vector<int> FullFrame;
    int CRCcheck;
};
