// STRING VECTOR EXAMPLE 
// CPP program to illustrate 
// Implementation of begin() function 
#include <iostream> 
#include <string> 
#include <vector> 
using namespace std;
int r(vector<int> v1, int n);
int r(vector<int> v1, int n) {


	// using begin() to print vector 
	for (auto it = v1.begin();
		it != v1.end(); ++it)
		cout << ' ' << *it;

};

int main()
{

	cout << "it works" << endl;
	return 0;
}