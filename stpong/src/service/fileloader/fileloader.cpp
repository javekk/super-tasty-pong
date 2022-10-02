
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


ReadTexture readTexture(const char *filePath){
    ReadTexture texture;
    std::string classPath =  __FILE__;
    std::string rootPath = classPath.substr(0, classPath.find("stpong/src/service/fileloader/fileloader.cpp"));
    std::string absPath = rootPath + ASSETS_DIR + "/" + filePath;

    int width, height, nrChannels;
    unsigned char *data = stbi_load(absPath.c_str(), &width, &height, &nrChannels, 0);
    if (!data){
        std::cerr << "Failed to load texture: could not read file " 
                  << absPath << ". File does not exist." << std::endl;
    }
    texture.width = width;
    texture.height = height;
    texture.data = data;
    return texture;
}

void freeTexture(unsigned char *data){
    stbi_image_free(data);
}