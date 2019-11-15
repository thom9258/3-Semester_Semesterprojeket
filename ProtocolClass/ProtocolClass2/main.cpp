#include <iostream>
#include <string>
#include "Protokol.hpp"
#include "Binary.hpp"
int main()
{
//    std::string input;
//    
//    std::cout << "Input the transmitted sentence" << std::endl;
//    std::getline(std::cin, input);
//    std::replace(input.begin(), input.end(),' ', '_');
//    
//    Protokol p1(input);
//    
//    int sf = 0;
//    int ul;
//    
//    while (sf != 1) {
//        p1.divider();
//        Binary FullFrame(p1.numbering());
////        std::cout << p1.getFS() << std::endl;
////        std::cout << p1.getF16() << std::endl;
////        std::cout << p1.numbering() << std::endl;
////        std::cout << p1.getFramecounter() << std::endl;
//        p1.flagDetermine();
//        sf = p1.getSF();
//        ul = p1.getUL();
//        Binary flag({0,0,ul,sf});
//        FullFrame = FullFrame.BinaryAppend(FullFrame, flag);
//        
//        for(int i = 0; i < p1.getF16().length(); i++)
//        {
//            Binary singleChar(p1.getF16()[i]);
//            FullFrame = FullFrame.BinaryAppend(FullFrame, singleChar);
//            
//        }
//
//        std::string CRCstring = p1.senderCRC(FullFrame.GetData());
//        
//        Binary CRC(CRCstring);
//        FullFrame = FullFrame.BinaryAppend(FullFrame, CRC);
//        
//        
//        std::cout << FullFrame << std::endl;
//        

	std::vector<int> inp = { 1,1,1,1,0,0,1,0 };

	std::vector<int> outp = SenderCRC(inp);

	for (int i = 0; i < outp.size(); i++)
	{
		std::cout << outp[i];
    }

	

    return 0;
}
