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
    
    int a = 0;
    
    while (a != 1) {
        p1.divider();
        p1.numbering();
        std::cout << p1.getFS() << std::endl;
        std::cout << p1.getF16() << std::endl;
        std::cout << p1.numbering() << std::endl;
        std::cout << p1.getFramecounter() << std::endl;
        p1.flagDetermine();
        a = p1.getSF();
        std::cout << a << std::endl;
    }

    
    
    return 0;
}
