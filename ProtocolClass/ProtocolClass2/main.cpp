#include <iostream>
#include <string>
#include "Protokol.hpp"
#include "Binary.hpp"
int main()
{
    std::string input;
    
    std::cout << "Input the transmitted sentence" << std::endl;
    std::getline(std::cin, input);
    
    Protokol p1(input);
    
    std::string input2 = p1.getFS();
    
    int sf = 0;
    int ul;
    
    while (sf != 1) {
        p1.divider();
        Binary b1(p1.numbering());
//        std::cout << p1.getFS() << std::endl;
//        std::cout << p1.getF16() << std::endl;
//        std::cout << p1.numbering() << std::endl;
//        std::cout << p1.getFramecounter() << std::endl;
        p1.flagDetermine();
        sf = p1.getSF();
        ul = p1.getUL();
        Binary b2({0,0,ul,sf});
        b1 = b1.BinaryAppend(b1, b2);
        //INSERT FIRST_16 APPEND HERE

        std::cout << b1 << std::endl;
    }

    return 0;
}
