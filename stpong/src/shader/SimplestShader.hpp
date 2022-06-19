#ifndef SIMPLEST_SHADER_HPP
#define SIMPLEST_SHADER_HPP
#pragma once



// System headers
#include <glad/glad.h>

// Standard headers
#include <cassert>
#include <fstream>
#include <memory>
#include <string>

class SimplestShader {

    public:
        SimplestShader(){ 
            mProgram = glCreateProgram(); 
        }


    private:
        // Private member variables
        GLuint mProgram;
};



#endif