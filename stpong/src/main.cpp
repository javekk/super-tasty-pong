
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "IO/window/window.hpp"
#include "program.hpp"

#include "settings.hpp"


int main(int argc, char *argv[]){

    std::cout << "Super Tasty Pong v" 
              << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH
              << std::endl;

    GLFWwindow* window = initialise();

    runProgram(window);
    
    glfwTerminate();
    
    return EXIT_SUCCESS;
}

