#include <iostream>
#include "ProtocolReceiver.h"
#include "BinaryReceiver.h"

void printVec(vector<int> inp, string mess)
{
	cout << mess << ": [ ";
	for (int i = 0; i < inp.size(); i++) { cout << inp[i] << " "; }
	cout << "]" << endl;
}

int main()
{
    std::vector<int> v1{0,0,0,0,0,0,1,1,0,1,1,0,1,0,0,0,1,0,1,0,1,0,0,0};
	printVec(v1, "start message");


    ProtocolReceiver p1(v1);
	if ( p1.CheckCRC() == true )
	{
		std::cout << "true" << std::endl;
		// if true, keep going
	}
	else
	{
		std::cout << "false" << std::endl;
	}

    p1.numberingRec(p1.getData());
    p1.flagdetermine();
    p1.databytesDetermine();
    
    
    std::vector<int> myvec2 = p1.getData();
    
	printVec(myvec2, "something");


    
}
