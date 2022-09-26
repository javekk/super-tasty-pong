#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#pragma once

#include <string>
#include <glad/glad.h> 

class Texture{
    public:
        unsigned int ID;

        // in Pixels 
        unsigned int width, height; 

        // image Data
        unsigned char *data;

        // format of texture object
        unsigned int internalFormat; 
        // format of loaded image
        unsigned int imageFormat; 

        // texture configuration
        unsigned int SWrap; 
        unsigned int TWrap; 
        unsigned int minFilter; 
        unsigned int maxFilter; 

        Texture();

        Texture generate(
            std::string imgPath
            , GLint wrappingMethod = GL_REPEAT
            , GLint filteringMethod = GL_LINEAR
        );

        void bind() const;
};

#endif