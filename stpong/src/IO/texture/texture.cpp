#include <iostream>
#include <fstream>

#include "texture.hpp"
#include "settings.hpp"
#include "service/string/string.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


std::string getExt(std::string imgPath);
int getChannels(std::string imgPath);


unsigned int loadTexture(
    const char *imgPath,
    GLint wrappingMethod,
    GLint filteringMethod
){

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingMethod);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingMethod);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filteringMethod);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filteringMethod);

    // load and generate the texture
    std::string classPath =  __FILE__;
    std::string rootPath = classPath.substr(0, classPath.find("stpong/src/IO/texture/texture.cpp"));
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


// Private methods

std::string getExt(std::string imgPath) {
    return toUpperCase(imgPath.substr(imgPath.find_last_of('.')));
}

GLint getChannels(std::string imgPath){
    std::string ext = getExt(imgPath);
    if(ext.compare(".PNG") == 0)
        return GL_RGBA;
    else // .jpg
        return GL_RGB;
}   






