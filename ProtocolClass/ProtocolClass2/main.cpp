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
    
    std::string input2 = p1.getString();
    
    std::cout << input2.length() << std::endl;

    p1.divider();
    
    return 0;
    
}
