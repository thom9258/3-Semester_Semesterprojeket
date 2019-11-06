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
            first_16 = fullsentence;
            fullsentence.clear();
            return first_16;
            
        }
    };
    
    int numbering()
    {
        NumOfChar = first_16.length();
        return NumOfChar;
    };
    
    void getNumbering()
    {
        std::cout << NumOfChar;
    }
    
    void flagDetermine()
    {
        //Slut flag tjek
        if(fullsentence.length() == 0){
            sf = 1;
        }
        else{
            sf = 0;
        }
        
    }
    
    
    
    
    
    
    
private:
    std::vector<int> frame;
    std::string fullsentence;
    std::string first_16;
    int NumOfChar;
    //lige = 0, ulige = 1
    int sf, ul;
};

#endif /* Protokol_hpp */
