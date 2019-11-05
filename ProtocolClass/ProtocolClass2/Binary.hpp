#pragma once

#include<iostream>
#include <vector>
#include <initializer_list>
#include <math.h>

using namespace std;

class Binary
{
public:



	// filler constructor
	Binary(int size) : binLength(size)
	{
		for (int i = 0; i != binLength; i++)
		{
			data.push_back(0);
		}
	};


	// defined constructor as initlist
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


	// defined constructor taking ASCII characters as char
	Binary(char ch) : binLength(7)
	{
		int intch = (int)ch - '0';


		for (int n = 7; n != 0; n--)
		{
			if (intch < pow(2, n) - 1)
			{
				data.push_back(0);
			}
			else
			{
				intch -= pow(2, n) - 1;
				data.push_back(1);
			}
		}


	};



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
			out << input.GetData()[i]; // bug here, vector sometimes out of scope
		}
		return out;
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
	std::vector<int> data;
	int binLength = 0;

};