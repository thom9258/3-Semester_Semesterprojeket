#pragma once

#include<iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <math.h>
#include<cassert>
#include<algorithm>
#include<sstream>

using namespace std;

class Binary
{
public:
	// default constructor for non input
	Binary(void) : binLength(0) {};


	// vector constructor
	Binary(vector<int> vec) : data(vec), binLength(vec.size()) {};


	// constructor for integers 1 -> 16
	Binary(int input) : binLength(4)
	{
		input--;
		if (input < 16)
		{
			for (int i = 0; i != 4; i++)
			{
				data.push_back((input >> i) & 1);
			}
			reverse(data.begin(), data.end());
		}
		else {
			assert("number is over 16!");
		}
		// 1 er alts� 0000 og 16 er alts� 1111
		// der skal derfor plusses 1 p� modtager siden
	};


	// defined constructor as initializer list
	Binary(initializer_list<int> base)
		: binLength(base.size())
	{
		for (int i = 0; i != binLength; i++)
		{
			data.push_back(base.begin()[i]);
		}
	};


	// defined constructor taking another Binary 
	Binary(Binary& bin) : binLength(bin.binLength), data(bin.data) {};


	// asdasdsddefined constructor tadasdasking a string of 1 and 0 as char
	Binary(string strBin)
	{
		for (int i = 0; i < strBin.size(); i++) 
		{
			if (strBin[i] == '1') 
			{
				data.push_back(1);
			}
			else
			{
				data.push_back(0);
			}
			binLength = data.size();
		}

	/*	istringstream iss(strBin);
		vector<int> resVec;
		int number;
		while (iss >> number)
		{
			resVec.push_back(number);
		}
		data = resVec;
		binLength = resVec.size();*/
	};

	// converts a character into a binary value with padding (to get the size to be 8 bits long)
	Binary(char character)
	{
		int integ = int(character);
		string bin = "";

		int i = integ;
		while (i > 0) // converts integer into binary
		{
			(i % 2) ? bin.push_back('1') : // if sentence that needs reformatting
				bin.push_back('0');
			i /= 2;
		}
		reverse(bin.begin(), bin.end());

		data = strToVec(bin);

		data.insert(data.begin(), 0);

		if (integ <= 64) {
			data.insert(data.begin(), 0);
		}

		binLength = data.size();
	}



	// appends a binary number onto another binary number
	Binary BinaryAppend(Binary num1, Binary num2)
	{
		Binary result = num1;
		result.SetLength(num1.GetLength() + num2.GetLength());

		for (int i = 0; i < num2.GetLength(); i++)
		{
			result.data.push_back(num2.data[i]);
		}
		return result;
	};

	// operator overload of the << operator for printing with cout
	friend ostream& operator<<(ostream& out, Binary& input)
	{
		for (int i = 0; i < input.GetLength(); i++)
		{
			out << input.GetData()[i];
		}
		return out;
	}

	// turns strings into vectors
	vector<int> strToVec(string str)
	{
		istringstream iss(str);
		vector<int> resVec;
		int number;
		while (iss >> number)
		{
			resVec.push_back(number);
		}
		return resVec;
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