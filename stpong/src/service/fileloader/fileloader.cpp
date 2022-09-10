
#include "fileloader.hpp"
#include <iostream>
#include <fstream>
#include "settings.hpp"


std::string readFile(const char *filePath) {

    std::string classPath =  __FILE__;
    std::string rootPath = classPath.substr(0, classPath.find("stpong/src/service/fileloader/fileloader.cpp"));
    std::string absPath = rootPath + SHADERS_DIR + "/" + filePath;

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
