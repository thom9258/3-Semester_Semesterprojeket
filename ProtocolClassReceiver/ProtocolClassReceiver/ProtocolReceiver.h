#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>


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
    
	//check crc
    
    int getsf(){
        return sf;
    }

    int getul(){
        return ul;
    }
    
    std::vector<int> databytesDetermine()
    {
        FullFrame.erase(FullFrame.begin(), FullFrame.begin()+8);
        
        FullFrame.erase(FullFrame.end()-8, FullFrame.end());
        
        return FullFrame;
    }
    

private:
	std::vector<int> FullFrame;
    int numbering;
    int sf = 0, ul = 0;
};
