#include <iostream>
#include <string>
#include "Protokol.hpp"
#include "Binary.hpp"
int main()
{
    std::string input;
    
    std::cout << "Input the transmitted sentence" << std::endl;
    std::getline(std::cin, input);
    std::replace(input.begin(), input.end(),' ', '_');
    
    Protokol p1(input);
    
    int sf = 0;
    int ul;
    
    while (sf != 1) {
        p1.divider();
        Binary FullFrame(p1.numbering());
        std::cout << FullFrame.GetLength() << std::endl;
//        std::cout << p1.getFS() << std::endl;
//        std::cout << p1.getF16() << std::endl;
//        std::cout << p1.numbering() << std::endl;
//        std::cout << p1.getFramecounter() << std::endl;
        p1.flagDetermine();
        sf = p1.getSF();
        ul = p1.getUL();
        Binary flag({0,0,ul,sf});
        FullFrame = FullFrame.BinaryAppend(FullFrame, flag);
        std::cout << FullFrame.GetLength() << std::endl;
        for(int i = 0; i < p1.getF16().length(); i++)
        {
            Binary singleChar(p1.getF16()[i]);
            FullFrame = FullFrame.BinaryAppend(FullFrame, singleChar);
            
        }
        

        //CRC here
        
//        std::cout << FullFrame << std::endl;
//
//        std::vector<int> sd = FullFrame.GetData();
//
//        std::cout << sd.size() << std::endl;
//
//        for (int i = 0; i < sd.size(); i++) {
//            std::cout << sd[i];
//        }
//
//        std::vector<int> myvec = {1, 0, 0};
//
//        std::cout << myvec.size() << std::endl;
        
        
        


//        std::string result;
//        for(int i=0; i < framesize; i++){
//            if (FullFrame.GetData()[i] == 1) {
//                result.push_back('1');
//            }
//            else{
//                result.push_back('0');
//            }
//        }
        
        

    return 0;
    }
}
