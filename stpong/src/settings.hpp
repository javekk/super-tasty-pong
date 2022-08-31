// Preprocessor directives
#ifndef SETTINGS_HPP
#define SETTINGS_HPP
#pragma once

#include <stpong/src/stpongConfig.hpp>

// Standard headers
#include <string>

// Constants
const int VERSION_MAJOR = stpong_VERSION_MAJOR;
const int VERSION_MINOR = stpong_VERSION_MINOR;
const int VERSION_PATCH = stpong_VERSION_PATCH;

const std::string SHADERS_DIR = stpong_SHADERS_DIR;
const std::string ASSETS_DIR  = stpong_ASSETS_DIR;

#endif