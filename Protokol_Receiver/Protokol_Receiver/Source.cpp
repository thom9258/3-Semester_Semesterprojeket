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

	vector<int> v1{ 1, 2, 3, 4, 5 };
	int r(vector<int> v1, 4);

	system("pause");
	return 0;
}