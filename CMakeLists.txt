cmake_minimum_required(VERSION 3.10)

# General
set(
    PROJECT_NAME 
    stpong
)
set(
    STPONG_ROOT_DIR
    stpong
)
set(
    STPONG_SOURCE_DIR
    ${STPONG_ROOT_DIR}/src
)
set(
    STPONG_VENDOR_DIR
    ${STPONG_ROOT_DIR}/vendor
)
set(
    STPONG_SHADERS_DIR
    ${STPONG_ROOT_DIR}/shaders
)

# specify the C++ standard
set(
    CMAKE_CXX_STANDARD 
    14
)
set(
    CMAKE_CXX_STANDARD_REQUIRED 
    True
)

# set the project name and version
project(
    ${PROJECT_NAME} 
    VERSION 
    1.0.0
)


# CMake setup
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++14")
  if(NOT WIN32)
    set(GLAD_LIBRARIES dl)
  endif()
endif()


# GLFW options
option(GLFW_INSTALL OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(${STPONG_VENDOR_DIR}/glfw)

# Set include paths
include_directories(
    ${STPONG_SOURCE_DIR}
    ${STPONG_VENDOR_DIR}/glad/include/
    ${STPONG_VENDOR_DIR}/glfw/include/
    ${STPONG_VENDOR_DIR}/glm/
    ${STPONG_VENDOR_DIR}/stb/
)


file(
    GLOB VENDORS_SOURCES 
        ${STPONG_VENDOR_DIR}/glad/src/glad.c
)
file(
    GLOB_RECURSE STPONG_HEADERS 
        ${STPONG_SOURCE_DIR}/*.hpp.in 
        ${STPONG_SOURCE_DIR}/*.hpp 
        ${STPONG_SOURCE_DIR}/*.h
)
file(
    GLOB_RECURSE STPONG_SOURCES 
        ${STPONG_SOURCE_DIR}/*.cpp
        ${STPONG_SOURCE_DIR}/*.cxx
        ${STPONG_SOURCE_DIR}/*.cc
        ${STPONG_SOURCE_DIR}/*.c
)
file(
    GLOB_RECURSE STPONG_SHADERS 
        ${STPONG_SHADERS_DIR}/*.comp
        ${STPONG_SHADERS_DIR}/*.frag
        ${STPONG_SHADERS_DIR}/*.geom
        ${STPONG_SHADERS_DIR}/*.vert
        ${STPONG_SHADERS_DIR}/*.glsl
)
file(
    GLOB STPONG_CONFIGS 
        CMakeLists.txt
        .gitignore
        .gitmodules
)


# config file
configure_file(
    ${STPONG_SOURCE_DIR}/stpongConfig.hpp.in 
    ${STPONG_SOURCE_DIR}/stpongConfig.hpp
)



source_group ("headers" FILES ${STPONG_HEADERS})
source_group ("shaders" FILES ${STPONG_SHADERS})
source_group ("sources" FILES ${STPONG_SOURCES})
source_group ("vendors" FILES ${VENDORS_SOURCES})


add_definitions(
    -DGLFW_INCLUDE_NONE
    -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
)

# add the executable
add_executable(
    ${PROJECT_NAME} 
    ${STPONG_SOURCES} 
    ${STPONG_HEADERS}
    ${STPONG_SHADERS} 
    ${STPONG_CONFIGS}
    ${VENDORS_SOURCES}
)

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC 
    "${PROJECT_BINARY_DIR}" 
)

target_link_libraries(
    ${PROJECT_NAME}
    glfw
    ${GLFW_LIBRARIES}
    ${GLAD_LIBRARIES}
)

set_target_properties(
    ${PROJECT_NAME} 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY 
    ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
)

