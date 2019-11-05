#include <stdio.h>
#include <vector>
#include <initializer_list>

class Binary {
    
public:
    Binary(std::initializer_list<int> base);
    
    std::vector<int> Append(Binary base, Binary append);
    
    
    
private:
    std::vector<int> data;
    
};
