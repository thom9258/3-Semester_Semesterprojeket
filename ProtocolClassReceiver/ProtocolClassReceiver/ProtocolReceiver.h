#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

class ProtocolReceiver
{
public:
	ProtocolReceiver(std::vector<int> input) : FullFrame(input) {};

	//check crc

	//RecNumbering

	//RecFlagDetermine

	//ConvertData

    
private:
	std::vector<int> FullFrame;
};
