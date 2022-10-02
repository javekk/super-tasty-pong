#ifndef FILELOADER_HPP
#define FILELOADER_HPP
#pragma once

#include <string>
#include <tuple>

std::string readShader(const char *filePath); 


class ReadTexture{
    public:
        int width, height; 
        unsigned char* data;
};

ReadTexture readTexture(const char *filePath);
void freeTexture(unsigned char *data); 

#endif