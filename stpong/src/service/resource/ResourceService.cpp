
#include "ResourceService.hpp"

std::map<std::string, Shader> ResourceService::Shaders;
std::map<std::string, Texture> ResourceService::Textures;

Shader ResourceService::loadShader(
    const char *vertexPath
    , const char *fragmentPath
    , const char *geometryPath
    , std::string name
){
    Shaders[name] = Shader(vertexPath, fragmentPath, geometryPath);
    Shaders[name].use();
    return Shaders[name];
}

Shader ResourceService::getShader(std::string name){
    return Shaders[name];
}


Texture ResourceService::loadTexture(
    const char *file
    , std::string name
){
    Texture texture;
    texture.generate(file);
    Textures[name] = texture;
    return Textures[name];
}

Texture ResourceService::getTexture(std::string name){
    return Textures[name];
}


void ResourceService::clear(){

    for (auto shader: Shaders)
        glDeleteProgram(shader.second.ID);

    for (auto texture: Textures)
        glDeleteTextures(1, &texture.second.ID);
}
