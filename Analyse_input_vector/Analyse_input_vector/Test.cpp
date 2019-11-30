#include <iostream>
#include <string>
#include <vector>
#include <analyse_vector.h>


using namespace std;



int main() {
	vector<int>v1{ 1,1,1,1 };
	analyse_vector::getVectorLength(v1);
	return 0;
}