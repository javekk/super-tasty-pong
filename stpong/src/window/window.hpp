#ifndef WINDOW_HPP
#define WINDOW_HPP
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebufferSizeCallback(GLFWwindow *window, int width, int height);

GLFWwindow* initialise();

#endif