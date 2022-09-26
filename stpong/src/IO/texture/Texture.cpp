#include <iostream>
#include <fstream>

#include "Texture.hpp"
#include "service/fileloader/fileloader.hpp"
#include "service/string/string.hpp"
#include <tuple>


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


Texture::Texture(): 
    width(0)
    , height(0)
    , internalFormat(GL_RGB)
    , imageFormat(GL_RGB)
    , SWrap(GL_REPEAT)
    , TWrap(GL_REPEAT)
    , minFilter(GL_LINEAR)
    , maxFilter(GL_LINEAR)
{
    glGenTextures(1, &this->ID);
}

Texture Texture::generate(
    std::string imgPath
    , GLint wrappingMethod
    , GLint filteringMethod
){  

    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);

    this->SWrap = wrappingMethod;
    this->TWrap = wrappingMethod;
    this->minFilter = filteringMethod;
    this->maxFilter = filteringMethod; 

    // width, height, data TODO(use a class)
    std::tuple<int, int, unsigned char*> rawTexture = readTexture(imgPath.c_str());
    this->width = std::get<0>(rawTexture);
    this->height = std::get<1>(rawTexture);
    this->data = std::get<2>(rawTexture);

    this->imageFormat = getChannels(imgPath);

    if (data){
        glTexImage2D(
            GL_TEXTURE_2D
            , 0
            , this->internalFormat
            , this->width
            , this->height
            , 0
            , this->imageFormat
            , GL_UNSIGNED_BYTE
            , this->data
        );
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cerr << "Failed to load texture: could not read file " 
                  << imgPath << ". File does not exist." << std::endl;
    }

    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->SWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->TWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->maxFilter);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    freeTexture(data);
    return *this;
}

void Texture::bind() const{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
