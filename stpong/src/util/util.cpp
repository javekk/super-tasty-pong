#include <iostream>
#include <string>
#include <fstream>

#include <glad/glad.h> 

#include "util.hpp"
#include "settings.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


std::string getExt(std::string imgPath);

int getChannels(std::string imgPath);



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
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, getChannels(imgPath), GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cerr << "Failed to load texture: could not read file " 
                  << absPath << ". File does not exist." << std::endl;
    }
    stbi_image_free(data);
    return texture;
}


std::string toUpperCase(std::string str){
    std::string result = "";
    int length = str.length();
    for (int i = 0; i < length; i++) 
        result += toupper(str[i]);
    return result;
}


// Private methods

std::string getExt(std::string imgPath) {
    return toUpperCase(imgPath.substr(imgPath.find_last_of('.')));
}

int getChannels(std::string imgPath){
    std::string ext = getExt(imgPath);
    if(ext.compare(".PNG") == 0)
        return GL_RGBA;
    else // .jpg
        return GL_RGB;
}   






