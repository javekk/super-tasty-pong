#ifndef UTIL_HPP
#define UTIL_HPP
#pragma once

#include <string>
#include <glad/glad.h> 

std::string readFile(const char *filePath); 

unsigned int loadTexture(
    const char *imgPath,
    GLint wrappingMethod = GL_REPEAT
);

std::string toUpperCase(std::string str); 

#endif