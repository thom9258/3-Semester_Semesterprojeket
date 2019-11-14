#include "Vector_analyse.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


Vector_analyse::Vector_analyse()
{
}



Vector_analyse::~Vector_analyse()
{
}
vector <int> Vector_analyse::getVectorLength(vector<int> v1) {
	vector <int> lengthVector;
	for (int i = 0; i < 4; i++) {


		lengthVector.push_back(v1.at(i));


	}
	return lengthVector;
};