#include <iostream>
#include <string>
#include "Protokol.hpp"
#include "Binary.hpp"

int divider(std::string input)
{
    std::string first_16;
    if (input.length() > 16) {
       first_16 = input.substr(0,16);
        std::cout << first_16;
    }
    else{
        std::cout << input;
    }
    return 0;
}

int main()
{
    std::string input;
    std::cout << "Input the transmitted sentence" << std::endl;
    std::getline(std::cin, input);
    std::cout << input.length() << std::endl;
    
    divider(input);
    
    return 0;
}
