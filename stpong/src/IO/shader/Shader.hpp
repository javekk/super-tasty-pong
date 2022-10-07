#ifndef SHADER_HPP
#define SHADER_HPP

  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
  

class Shader {

    public:
        unsigned int ID;
        
        Shader();

        Shader(
            const char *vertexPath
            , const char *fragmentPath
            , const char *geometryPath = nullptr
        );
        
        Shader &use();

        void setBool(const std::string &name, const bool value) const;  
        void setInt(const std::string &name, const int value) const;   
        void setFloat(const std::string &name, const float value) const;
        void setVector2f(const std::string &name, const glm::vec2 &value) const;
        void setVector3f(const std::string &name, const glm::vec3 &value) const;
        void setVector4f(const std::string &name, const glm::vec4 &value) const;
        void setMatrix4(const std::string &name, const glm::mat4 &matrix) const;

    private:

        void checkCompileErrors(
            unsigned int shader
            , std::string type
        );

        unsigned int loadSingleShader(
            const char *path
            , GLint shaderType
            , std::string type
        );
};


#endif