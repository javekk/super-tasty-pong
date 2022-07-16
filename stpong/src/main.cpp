// A simple program that computes the square root of a number
#include <iostream>
#include <string>
#include <fstream>


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stpong/src/stpongConfig.hpp"
#include "window/window.hpp"


void processInput(GLFWwindow *window);
std::string readFile(const char *filePath); 


int main(int argc, char *argv[]){

    std::cout << "Super Tasty Pong "
              << stpong_VERSION_MAJOR << "." << stpong_VERSION_MINOR << "." << stpong_VERSION_PATCH
              << std::endl;

    GLFWwindow* window = initialise();

    std::string vertShaderStr = readFile("shader/simplestvert.glsl");
    std::string fragShaderStr = readFile("shader/simplestfrag.glsl");
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    // shader and vertex
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragmentShader);

    // create shader program obj to link shaders
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        -0.9f, -0.5f, 0.0f, // left
        -0.0f, -0.5f, 0.0f, // right
        -0.35f, 0.5f, 0.0f, // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // render loop
    while (!glfwWindowShouldClose(window)){

        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


std::string readFile(const char *filePath) {

    std::string classPath =  __FILE__;
    std::string rootPath = classPath.substr(0, classPath.find("src/main.cpp"));
    std::string absPath = rootPath + filePath;

    std::string content;
    std::ifstream fileStream(absPath, std::ios::in);
    
    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << absPath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}