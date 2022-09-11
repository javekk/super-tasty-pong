#include <string>
#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "program.hpp"
#include "IO/shader/Shader.hpp"
#include "IO/texture/texture.hpp"


float getYOffset(float previousYOffset, GLFWwindow *window);
float getXOffset(float previousXOffset, GLFWwindow *window);
float getSize(float previousSizeTransformation, GLFWwindow *window);

glm::mat4 getTransformationMatrix(float size, float xOffset, float yOffset);
void handleEscButton(GLFWwindow *window);


void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void runProgram(GLFWwindow* window){

    // shader and vertex

    // Load shader from file
    Shader mShader("simplestvert.glsl", "simplestfrag.glsl");

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // get texture
    unsigned int wallTexture = loadTexture("wall.jpg", GL_REPEAT, GL_NEAREST);
    unsigned int awesomeTexture = loadTexture("awesomeface.png", GL_MIRRORED_REPEAT, GL_NEAREST);

    mShader.use(); 
    mShader.setInt("texture1", 0); 
    mShader.setInt("texture2", 1); 

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    float xOffset = 0.0;
    float yOffset = 0.0;
    float size = 1.0;
    while (!glfwWindowShouldClose(window)){

        handleEscButton(window);
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, wallTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, awesomeTexture);

        // draw
        glm::mat4 transform = getTransformationMatrix(size, xOffset, yOffset);
        mShader.use();
        unsigned int transformLoc = glGetUniformLocation(mShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        xOffset = getXOffset(xOffset, window);
        yOffset = getYOffset(yOffset, window);
        size = getSize(size, window);

        glBindTexture(GL_TEXTURE_2D, wallTexture);
        glBindTexture(GL_TEXTURE_2D, awesomeTexture);

        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // De-allocate all resources 
    glDeleteVertexArrays(1, VAOs);
    glDeleteBuffers(1, VBOs);
    glDeleteBuffers(1, EBOs);
}


void handleEscButton(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

float getYOffset(float previousYOffset, GLFWwindow *window) {

    float yOffset = previousYOffset; 
    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        yOffset += 0.01f; 
        if(yOffset >= 1.0f)
            yOffset = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        yOffset -= 0.01f; 
        if (yOffset <= -1.0f)
            yOffset = -1.0f;
    }
    return yOffset;
}


float getXOffset(float previousXOffset, GLFWwindow *window) {

    float xOffset = previousXOffset; 

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        xOffset += 0.01f; 
        if(xOffset >= 1.0f)
            xOffset = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        xOffset -= 0.01f; 
        if (xOffset <= -1.0f)
            xOffset = -1.0f;
    }
    return xOffset;
}


float getSize(float previousSizeTransformation, GLFWwindow *window){

    float newSizeTransformation = previousSizeTransformation;
    if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS){
        newSizeTransformation += 0.01f; 
        if(newSizeTransformation >= 2.0f)
            newSizeTransformation = 2.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS){
        newSizeTransformation -= 0.01f; 
        if (newSizeTransformation <= 0.1f)
            newSizeTransformation = 0.1f;
    }
    return newSizeTransformation;
}


glm::mat4 getTransformationMatrix(float size, float xOffset, float yOffset){
    glm::mat4 transform = glm::mat4(1.0f); 
    transform = glm::scale(transform, glm::vec3(size));
    transform = glm::translate(transform, glm::vec3(xOffset, yOffset, 0.0f));
    return transform;
}