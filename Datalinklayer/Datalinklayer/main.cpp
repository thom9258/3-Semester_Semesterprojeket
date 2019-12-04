#include <iostream>
#include "Binary.h"
#include "Protocol.h"

std::vector<int> stringToVec(std::string input)
{
    std::replace(input.begin(), input.end(),' ', '_');
    Protokol p1(input);
    int sf = 0;
    int ul;
        while (sf != 1) {
            p1.divider();
            Binary FullFrame(p1.numberingSender());
    //        std::cout << p1.getFS() << std::endl;
    //        std::cout << p1.getF16() << std::endl;
    //        std::cout << p1.numbering() << std::endl;
    //        std::cout << p1.getFramecounter() << std::endl;
            p1.flagDetermineSender();
            sf = p1.getSF();
            ul = p1.getUL();
            Binary flag({0,0,ul,sf});
            FullFrame = FullFrame.BinaryAppend(FullFrame, flag);
            for(int i = 0; i < p1.getF16().length(); i++)
            {
                Binary singleChar(p1.getF16()[i]);
                FullFrame = FullFrame.BinaryAppend(FullFrame, singleChar);
                
            }
            std::string stringFrame = FullFrame.returnString();
            
            Binary FullFrame2(p1.SenderCRC(stringFrame));
    //        std::cout << FullFrame << std::endl;
            return FullFrame2;
            
            // GIVE FULLFRAME 2 TO PHYSICAL LAYER, THIS IS THE FINAL BIT STRING !!
            
        }
}

int main()
{
    
    return 0;
}
