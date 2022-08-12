#include <string>
#include <iostream>
#include <cmath>

#include "program.hpp"
#include "util/util.hpp"
#include "shader/Shader.hpp"


void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void runProgram(GLFWwindow* window){

    // shader and vertex

    // Load shader from file
    Shader mShader("simplestvert.glsl", "simplestfrag.glsl");

    float vertices[] = {
        // Positions         // Colors
        -0.1f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f, // top right
        -0.1f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3,   // first triangle
        1, 2, 3,    // second triangle
    };  

    // Vertex Buffer Objects, Vertex Array Object, Element Buffer Objects 
    unsigned int VBOs[1], VAOs[1], EBOs[1]; 
    glGenVertexArrays(1, VAOs);
    glGenBuffers(1, VBOs);
    glGenBuffers(1, EBOs);

    // set up first rectangle
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window)){

        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        float timeValue = glfwGetTime();
        float offset = (sin(timeValue) / 2.0f) + 0.25f;
        mShader.setFloat("xOffset", offset);
        mShader.use();
        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}