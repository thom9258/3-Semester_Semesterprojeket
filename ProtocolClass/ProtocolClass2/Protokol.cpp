#include "Protokol.hpp"
#include <iostream>
#include <string>

std::string Protokol::divider(std::string input)
{
    std::string first_16;
    if (input.length() > 16) {
       std::string divided = input.substr(0,16);
        std::cout << divided;
    }
    else{
        std::cout << input;
    }
    return input;
}
