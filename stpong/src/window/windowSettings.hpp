// Preprocessor directives
#ifndef WINDOW_SETTING_HPP
#define WINDOW_SETTING_HPP
#pragma once

// System Headers
#include <glad/glad.h>

// Standard headers
#include <string>

// Constants
const int         windowWidth     = 1024;
const int         windowHeight    = 768;
const std::string windowTitle     = "Super Tasty Pong";
const GLint       windowResizable = GL_FALSE;
const int         windowSamples   = 4;

#endif