#include "string.hpp"

std::string toUpperCase(std::string str){
    std::string result = "";
    int length = str.length();
    for (int i = 0; i < length; i++) 
        result += toupper(str[i]);
    return result;
}