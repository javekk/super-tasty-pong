#include "Transformations.hpp"
#include <glm/gtc/matrix_transform.hpp>


Transformations::Transformations(
    float xOffset
    , float yOffset
    , float scale
    , float rotation
){
    this->xOffset = xOffset;
    this->yOffset = yOffset;
    this->scale = scale;
    this->rotation = rotation;
}


Transformations::Transformations(
    const Transformations& previousStatus
    , GLFWwindow *window
){
    this->xOffset = getXOffset(previousStatus.xOffset, window);
    this->yOffset = getYOffset(previousStatus.yOffset, window);
    this->scale = getScale(previousStatus.scale, window);
    this->rotation = getRotation(previousStatus.rotation, window);
}



float Transformations::getYOffset(
    float previousYOffset
    , GLFWwindow *window
) {
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

float Transformations::getXOffset(
    float previousXOffset
    , GLFWwindow *window
) {
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

float Transformations::getScale(
    float previousSize
    , GLFWwindow *window
){
    float newSize = previousSize;
    if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS){
        newSize += 0.01f; 
        if(newSize >= 2.0f)
            newSize = 2.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS){
        newSize -= 0.01f; 
        if (newSize <= 0.1f)
            newSize = 0.1f;
    }
    return newSize;
}

float Transformations::getRotation(
    float previousRotation
    , GLFWwindow *window
){
    float newRotation = previousRotation;

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        newRotation += 1.0f;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        newRotation -= 1.0f; 
    if (newRotation >= 360.0f)
        newRotation = 0.0f;
    return newRotation;
}


glm::mat4 Transformations::getTransformationMatrix(
    const Transformations& transformations
){
    glm::mat4 transform = glm::mat4(1.0f); 
    transform = glm::scale(transform, glm::vec3(transformations.scale));
    transform = glm::rotate(transform, glm::radians(transformations.rotation), glm::vec3(0.0, 0.0, 1.0));
    transform = glm::translate(transform, glm::vec3(transformations.xOffset, transformations.yOffset, 0.0f));
    return transform;
}
