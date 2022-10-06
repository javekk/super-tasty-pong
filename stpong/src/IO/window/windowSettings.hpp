#ifndef WINDOW_SETTINGS_HPP
#define WINDOW_SETTINGS_HPP
#pragma once

#include <glad/glad.h>

#include <string>

const int         windowWidth     = 1024;
const int         windowHeight    = 768;
const std::string windowTitle     = "Super Tasty Pong";
const GLint       windowResizable = GL_FALSE;
const int         windowSamples   = 4;

#endif