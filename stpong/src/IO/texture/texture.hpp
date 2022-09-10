#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#pragma once

#include <glad/glad.h> 

unsigned int loadTexture(
    const char *imgPath,
    GLint wrappingMethod = GL_REPEAT,
    GLint filteringMethod = GL_LINEAR
);

#endif