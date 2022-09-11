#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Transformations {

    public:
        float xOffset;
        float yOffset;
        float scale;
        float rotation;

        Transformations(
            float xOffset
            , float yOffset
            , float scale
            , float rotation
        );
        Transformations(
            const Transformations& previousStatus
            , GLFWwindow *window
        );
        glm::mat4 getTransformationMatrix(
            const Transformations& transformations
        );

    private: 
        float getYOffset(float previousYOffset, GLFWwindow *window);
        float getXOffset(float previousXOffset, GLFWwindow *window);
        float getScale(float previousSize, GLFWwindow *window);
        float getRotation(float previousRotation, GLFWwindow *window);
};

#endif