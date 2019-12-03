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
		std::cout << "CRC check is true" << std::endl;
		// if true, keep going
	}
	else
	{
		std::cout << "CRC check is false" << std::endl;
	}

    p1.numberingRec(p1.getData());
    p1.flagdetermine();
    p1.databytesDetermine();
    
    





	std::string fullMessage;
	 
	while (p1.getsf() != 1) 
	{

		// mik sindsygs kode som laver p1 objekterne og checker om alt er i orden


		std::vector<int> currVec = p1.getData();
		printVec(currVec, "curr data");


		std::string currMessage = p1.returnMessage(currVec);

		fullMessage += currMessage;
	}

	// giveToAPILayer(fullMessage);



	int a;
	std::cin >> a;
    
}
