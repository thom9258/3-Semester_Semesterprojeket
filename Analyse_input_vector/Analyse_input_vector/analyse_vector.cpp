#include "analyse_vector.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


analyse_vector::analyse_vector()
{
}
vector<int> analyse_vector::getVectorLength(vector<int> v1) {
	vector<int> lengthVector;
	for (int i = 0; i < 4; i++) {


		lengthVector.push_back(v1.at(i));
	};


	return lengthVector;
};
analyse_vector::~analyse_vector()
{
}
