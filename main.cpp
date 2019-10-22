#include <iostream>

std::string sender(std::string message, std::string CRC)
{

std::string encresult="";

    encresult += message;

    int n = CRC.length();

    for(int i = 1; i<=n-1; i++){
        encresult += '0';
    }
    for(int i = 0; i <= encresult.length()-n; ){
        for (int k=0; k<n; k++)
            encresult[i+k] = encresult[i+k]==CRC[k]? '0' : '1';
            for( ; i < encresult.length() && encresult[i] != '1'; i++);

    }

    std::string final = message + encresult.substr(encresult.length()-n+1);
    
    return final;
}


std::string receiver(std::string senderCRC, std::string CRC)
{
    for(int i=0; i<=senderCRC.length()-CRC.length(); ) {
        for(int k=0; k<CRC.length(); k++)
            senderCRC[i+k]=senderCRC[i+k]==CRC[k]? '0' : '1';
            for(; i < senderCRC.length() && senderCRC[i]!='1'; i++);
        }

    for( char i: senderCRC.substr(senderCRC.length()-CRC.length()+1) )
        if(i!='0'){
            std::string final = "ERRRROOROOROR";
            return final;
        }
    std::string final = "No error :)";
            return final;
}


int main()
{
    std::string message;
    std::cout << "Input message: " << std::endl;
    std::cin >> message;
    
    std::string CRC;
    std::cout << "Input CRC polynomial coefficients: " << std::endl;
    std::cin >> CRC;
    
//    std::cout << "CRC check done by sender side: " << std::endl;
    std::string senderCRC = sender(message, CRC);
//    std::cout << senderCRC << std::endl;
    
    std::string result = receiver(senderCRC, CRC);
    std::cout << result << std::endl;
}
