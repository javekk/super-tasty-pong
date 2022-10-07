
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "IO/window/window.hpp"
#include "IO/window/windowSettings.hpp"
#include "Program.hpp"

#include "settings.hpp"
#include "game/Game.hpp"

int main(int argc, char *argv[]){

    std::cout << "Super Tasty Pong v"
              << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH
              << ".❤️"
              << std::endl;

    GLFWwindow *window = initialise();
    Game superTastyPong(windowWidth, windowHeight);
    Program program(window, superTastyPong);
    program.run();

    glfwTerminate();

    return EXIT_SUCCESS;
}
