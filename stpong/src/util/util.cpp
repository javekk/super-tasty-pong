#include <iostream>
#include <string>
#include <fstream>

#include <glad/glad.h> 

#include "util.hpp"
#include "settings.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


std::string readFile(const char *filePath) {

    std::string classPath =  __FILE__;
    std::string rootPath = classPath.substr(0, classPath.find("stpong/src/util/util.cpp"));
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


unsigned int loadTexture(const char *imgPath){

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load and generate the texture
    std::string classPath =  __FILE__;
    std::string rootPath = classPath.substr(0, classPath.find("stpong/src/util/util.cpp"));
    std::string absPath = rootPath + ASSETS_DIR + "/" + imgPath;

    int width, height, nrChannels;
    unsigned char *data = stbi_load(absPath.c_str(), &width, &height, &nrChannels, 0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cerr << "Failed to load texture: could not read file " 
                  << absPath << ". File does not exist." << std::endl;
    }
    stbi_image_free(data);
    return texture;
}