
#include "fileloader.hpp"
#include <iostream>
#include <fstream>
#include "settings.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::string readShader(const char *filePath) {

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


std::tuple<int, int, unsigned char*> readTexture(const char *filePath){
    std::tuple<int, int, unsigned char*> ret;
    std::string classPath =  __FILE__;
    std::string rootPath = classPath.substr(0, classPath.find("stpong/src/service/fileloader/fileloader.cpp"));
    std::string absPath = rootPath + ASSETS_DIR + "/" + filePath;

    int width, height, nrChannels;
    unsigned char *data = stbi_load(absPath.c_str(), &width, &height, &nrChannels, 0);
    if (!data){
        std::cerr << "Failed to load texture: could not read file " 
                  << absPath << ". File does not exist." << std::endl;
    }
    std::get<0>(ret) = width;
    std::get<1>(ret) = height;
    std::get<2>(ret) = data;
    return ret;
}

void freeTexture(unsigned char *data){
    stbi_image_free(data);
}