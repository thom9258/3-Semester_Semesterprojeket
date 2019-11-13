#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

class ProtocolReceiver
{
public:
	ProtocolReceiver(std::vector<int> input) : FullFrame(input) {};

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

	//ConvertData

    
private:
	std::vector<int> FullFrame;
};
