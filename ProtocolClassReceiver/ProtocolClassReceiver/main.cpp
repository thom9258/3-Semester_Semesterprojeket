#include <iostream>
#include "ProtocolReceiver.h"
#include "BinaryReceiver.h"

int main()
{
    std::vector<int> v1{0,0,0,0,  0,0,1,1,   0,1,1,0   ,0,0,0,1,    0,0,0,1,     1,1,1,1};

    ProtocolReceiver p1(v1);
    
    p1.numberingRec(p1.getData());
    p1.flagdetermine();
    p1.databytesDetermine();
    
    
    std::vector<int> myvec2 = p1.getData();
    
    
    for (int i = 0; i < myvec2.size(); i++) {
        std::cout << myvec2[i];
    }


    
}
