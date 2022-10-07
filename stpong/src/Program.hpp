
#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "game/Game.hpp"

class Program {
    public:
        Game game;
        GLFWwindow* window;

        Program(GLFWwindow* window, Game game);

        int run();

    private:
        void handleEscButton();
        void keyCallback(
            GLFWwindow* window
            , int key
            , int scancode
            , int action
            , int mode
        );
};

#endif
