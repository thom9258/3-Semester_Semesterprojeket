#include <iostream>
#include "ProtocolReceiver.h"
#include "BinaryReceiver.h"

int main()
{
	std::vector<int> v1{ 0,0,0,1 };
	std::cout << ProtocolReceiver::getVectorLength(v1);
	std::cout <<"hello waorld";
	system("pause");
	//std::cout << ProtocolReceiver::getVectorLength(v1);
    
}
