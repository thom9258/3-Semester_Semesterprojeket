#ifndef Protokol_hpp
#define Protokol_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
class Protokol {
    
public:
    
    Protokol(std::string input) : fullsentence(input){};
    
    //Get the first 16 letters
        std::string getF16()
        {
            return first_16;
        }
    
    //Get the full sentence(the first 16 will be erased each time)
    
        std::string getFS()
        {
            return fullsentence;
        };
    
    std::string divider()
    {
        
        if (fullsentence.length() > 16) {
            first_16 = fullsentence.substr(0,16);
            fullsentence = fullsentence.erase(0,16);
            return first_16;
        }
        else{
            return fullsentence;
        }
    };
    
    
    
    
    
    
        
private:
    std::vector<int> frame;
    std::string fullsentence;
    std::string first_16;
};

#endif /* Protokol_hpp */
