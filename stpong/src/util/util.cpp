#include <iostream>
#include <string>
#include <fstream>

#include "util.hpp"

std::string readFile(const char *filePath) {

    std::string classPath =  __FILE__;
    std::string rootPath = classPath.substr(0, classPath.find("src/util/util.cpp"));
    std::string absPath = rootPath + filePath;

    std::string content;
    std::ifstream fileStream(absPath, std::ios::in);
    
    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << absPath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}