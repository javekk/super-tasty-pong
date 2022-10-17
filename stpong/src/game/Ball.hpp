#ifndef BALL_HPP
#define BALL_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "IO/texture/Texture.hpp"
#include "GameObject.hpp"

class Ball : public GameObject{

    public:
        float radius;
        bool stuck;

        Ball();
        Ball(
            glm::vec2 position
            , float radius
            , glm::vec2 velocity
            , Texture sprite
        );

        glm::vec2 move(float deltatime, unsigned int windowWidth);
        void reset(glm::vec2 position, glm::vec2 velocity);
};

#endif