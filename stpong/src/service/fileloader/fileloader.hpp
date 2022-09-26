#ifndef FILELOADER_HPP
#define FILELOADER_HPP
#pragma once

#include <string>
#include <tuple>

std::string readShader(const char *filePath); 

// return  width, height, data TODO(use a class)
std::tuple<int, int, unsigned char*> readTexture(const char *filePath);
void freeTexture(unsigned char *data); 

#endif