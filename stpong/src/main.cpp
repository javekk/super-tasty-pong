
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stpong/src/stpongConfig.hpp"
#include "window/window.hpp"
#include "program.hpp"


int main(int argc, char *argv[]){

    std::cout << "Super Tasty Pong" 
              << stpong_VERSION_MAJOR << "." << stpong_VERSION_MINOR << "." << stpong_VERSION_PATCH
              << std::endl;

    GLFWwindow* window = initialise();

    runProgram(window);
    
    glfwTerminate();
    
    return EXIT_SUCCESS;
}

