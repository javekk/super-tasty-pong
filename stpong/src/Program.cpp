#include <string>
#include <iostream>
#include <cmath>

#include <glm/gtc/type_ptr.hpp>

#include "Program.hpp"
#include "service/resource/ResourceService.hpp"

Program::Program(GLFWwindow* window, Game game):
    window(window)
    , game(game){}

int Program::run(){

    auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto me = (Program*) glfwGetWindowUserPointer(window);
        me->keyCallback(window, key, scancode, action, mods);
    };
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyCallback);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->game.init();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(this->window)){
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        this->game.processInput(deltaTime);
        this->game.update(deltaTime);
        this->game.render();

        glfwSwapBuffers(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
    }
    ResourceService::clear();
    return EXIT_SUCCESS;
}


void Program::handleEscButton(){
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, true);
}

void Program::keyCallback(
    GLFWwindow* window
    , int key
    , int scancode
    , int action
    , int mode
){
    
    this->handleEscButton();
    if (key >= 0 && key < 1024){
        if (action == GLFW_PRESS){
            std::cout << "Key press: " << key << std::endl;
            this->game.keys[key] = true;
        }
        else if (action == GLFW_RELEASE){
            std::cout << "Key released: " << key << std::endl;
            this->game.keys[key] = false;
        }
    }
}