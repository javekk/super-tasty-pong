#ifndef RESOURCESERVICE_HPP
#define RESOURCESERVICE_HPP
#pragma once

#include <map>
#include <string>

#include <glad/glad.h>

#include "IO/shader/Shader.hpp"
#include "IO/texture/Texture.hpp"

class ResourceService{
public:

    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture> Textures;

    static Shader loadShader(
        const char *vertexPath
        , const char *fragmentPath
        , const char *geometryPath
        , std::string name
    );
    static Shader getShader(std::string name);

    static Texture loadTexture(
        const char *file
        , std::string name
    );
    static Texture getTexture(std::string name);

    static void clear();
};


#endif