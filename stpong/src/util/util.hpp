#ifndef UTIL_HPP
#define UTIL_HPP
#pragma once

#include <string>

std::string readFile(const char *filePath); 

unsigned int loadTexture(const char *imgPath);

std::string toUpperCase(std::string str); 

#endif