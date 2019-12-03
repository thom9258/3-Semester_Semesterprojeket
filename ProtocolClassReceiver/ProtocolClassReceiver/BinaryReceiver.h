#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <math.h>
#include <cassert>
#include <algorithm>
#include <sstream>

using namespace std;

class BinaryRec
{
public:

	// vector constructor
	BinaryRec(vector<int> vec) : data(vec), binLength(vec.size()) {};

	// returning a char
	char BinToChar(void)
	{
		int result = 0;

		vector<int> binData = data;
		reverse(binData.begin(), binData.end());

		for (int i = 0; i < binData.size(); i++)
		{
			if (binData[i] == 1)
			{
				result += pow((binData[i] * 2), i);

			}
		}
		return result;
	}

	// getter functions 
	int GetLength(void)
	{
		return binLength;
	}

	vector<int> GetData(void)
	{
		return data;
	}


	friend ostream& operator<<(ostream& out, BinaryRec& input)
	{
		for (int i = 0; i < input.GetLength(); i++)
		{
			out << input.GetData()[i]; // bug here, vector sometimes out of scope
		}
		return out;
	}

	//setter functions
	void SetLength(int length) {
		binLength = length;
	}

private:
	//variable containing the binary "vector" in a format of integers of 0 and 1
	vector<int> data;
	// length of the above vector
	int binLength = 0;
};



