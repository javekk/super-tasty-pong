#include "Shader.hpp"
#include "service/fileloader/fileloader.hpp"
#include "settings.hpp"

#include <glad/glad.h> 

Shader::Shader() {}

Shader::Shader(
    const char *vertexPath
    , const char *fragmentPath
    , const char *geometryPath
){
    unsigned int vertex, fragment, gShader;

    vertex = this->loadSingleShader(vertexPath, GL_VERTEX_SHADER, "VERTEX");
    fragment = this->loadSingleShader(fragmentPath, GL_FRAGMENT_SHADER, "FRAGMENT");
    gShader = (geometryPath != nullptr) 
        ? this->loadSingleShader(geometryPath, GL_GEOMETRY_SHADER, "GEOMETRY") 
        : 0;
    
    this->ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if (geometryPath != nullptr)
        glAttachShader(ID, gShader);
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometryPath != nullptr)
        glDeleteShader(gShader);
}

Shader &Shader::use(){
    glUseProgram(this->ID);
    return *this;
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const { 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const { 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVector2f(const std::string &name, const glm::vec2 &value) const{
    glUniform2f(glGetUniformLocation(this->ID, name.c_str()), value.x, value.y);
}

void Shader::setVector3f(const std::string &name, const glm::vec3 &value) const{
    glUniform3f(glGetUniformLocation(this->ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVector4f(const std::string &name, const glm::vec4 &value) const{
     glUniform4f(glGetUniformLocation(this->ID, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const std::string &name, const glm::mat4 &matrix) const{
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, false, glm::value_ptr(matrix));
}

// Private

void Shader::checkCompileErrors(unsigned int shader, std::string type) {
    
    int success;
    char infoLog[1024];
    std::string sepator = "\n 😭😭😭😭😭😭 \n"; 
    if (type != "PROGRAM"){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " 
                    << type << "\n" << infoLog << sepator << std::endl;
        }
    }
    else{
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success){
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " 
                    << type << "\n" << infoLog << sepator << std::endl;
        }
    }
}

unsigned int Shader::loadSingleShader(
    const char *path
    , GLint shaderType
    , std::string type
){  
    unsigned int shader = glCreateShader(shaderType);
    std::string sShaderCode = readShader(path);
    const char *shaderCode = sShaderCode.c_str();
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    checkCompileErrors(shader, type);
    return shader;
}

    