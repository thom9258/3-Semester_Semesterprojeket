#ifndef Protokol_hpp
#define Protokol_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
class Protokol {
    
public:
    
    Protokol(std::string input) : fullsentence(input){};
    
    std::string getString()
    {
        return fullsentence;
    };
    
    void printdivider()
    {
        std::string first_16;
        
        if (fullsentence.length() > 16) {
            first_16 = fullsentence.substr(0,16);
            std::cout << first_16;
        }
        else{
            std::cout << fullsentence << std::endl;
        }
    };
    
    std::string divider()
    {
        std::string first_16;
        
        if (fullsentence.length() > 16) {
            first_16 = fullsentence.substr(0,16);
            return first_16;
        }
        else{
            return fullsentence;
        }
    };
    
    
    
    
    
private:
    std::vector<int> frame;
    std::string fullsentence;
};

#endif /* Protokol_hpp */
