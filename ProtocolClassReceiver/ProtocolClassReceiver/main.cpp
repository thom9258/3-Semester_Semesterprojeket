#include <iostream>
#include "ProtocolReceiver.h"
#include "BinaryReceiver.h"

bool errorCheck(ProtocolReceiver p1)
{
    bool final = true;
    if ( p1.CheckCRC() == true )
    {
        std::cout << "CRC check is true" << std::endl;
        // if true, keep going
    }
    else
    {
        std::cout << "CRC check is false" << std::endl;
        return final = false;
    }
    int a = p1.numberingRec(p1.getData());
    int b = p1.databytesDetermine().size();
    if (a*8 == b) {
        std::cout << "Number of bytes is correct" << std::endl;
    }
    else
    {
        std::cout << "Number of bytes is incorrect" << std::endl;
        return final = false;
    }
    
    if (p1.getframecounter() % 2 == p1.getul() ) {
        std::cout << "Correct even/odd frame received" << std::endl;
    }
    else {
        std::cout << "Not the even/odd frame I expected" << std::endl;
        return final = false;
    }
    return final;
}

void printVec(vector<int> inp, string mess)
{
	cout << mess << ": [ ";
	for (int i = 0; i < inp.size(); i++) { cout << inp[i] << " "; }
	cout << "]" << endl;
}



int main()
{
    std::vector<int> v1{1,1,1,1,0,0,0,1,0,1,1,0,0,1,0,0,0,1,1,0,0,1,0,1,0,1,1,1,0,1,0,0,0,1,0,1,1,1,1,1,0,1,1,0,0,1,0,0,0,1,1,0,0,1,0,1,0,1,1,1,0,1,0,0,0,1,1,0,1,0,0,0,0,1,0,1,1,1,1,1,0,1,1,0,0,0,0,1,0,1,1,0,1,0,0,0,0,1,1,0,0,1,0,0,0,1,1,0,1,0,0,0,0,1,1,0,0,0,0,1,0,1,1,0,1,0,0,0,0,1,1,0,0,1,0,0,1,1,1,1,1,0,1,1};
    
    
	printVec(v1, "start message");


    ProtocolReceiver p1(v1);
    
    errorCheck(p1);

    p1.numberingRec(p1.getData());
    p1.flagdetermine();
    p1.databytesDetermine();
    
    
        std::string fullMessage;
         
        while (p1.getsf() != 1)
        {
    
            // mik sindsygs kode som laver p1 objekterne og checker om alt er i orden
    
    
            std::vector<int> currVec = p1.getData();
            printVec(currVec, "curr data");
    
    
            std::string currMessage = p1.returnMessage();
    
            fullMessage += currMessage;
        }
    
        // giveToAPILayer(fullMessage);
    
    
    
        int a;
        std::cin >> a;
    


    
}
