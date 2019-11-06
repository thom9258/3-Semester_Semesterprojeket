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
    
    p1.divider();
    p1.numbering();
    std::cout << p1.getFS() << std::endl;
    std::cout << p1.getF16() << std::endl;
    std::cout << p1.numbering() << std::endl;
    
    
    return 0;
}
