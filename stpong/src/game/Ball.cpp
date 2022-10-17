#include "Ball.hpp"


Ball::Ball(): 
    GameObject(), 
    radius(12.5f), 
    stuck(true) { }


Ball::Ball(
    glm::vec2 pos
    , float radius
    , glm::vec2 velocity
    , Texture sprite
): GameObject(
        pos
        , glm::vec2(radius * 2.0f, radius * 2.0f)
        , sprite, glm::vec3(1.0f)
        , velocity
    )
    , radius(radius)
    , stuck(true) { }


glm::vec2 Ball::move(float deltatime, unsigned int windowHeight){
    if (!this->stuck){
        this->position += this->velocity * deltatime;
        if (this->position.y <= 0.0f){
            this->velocity.y = -this->velocity.y;
            this->position.y = 0.0f;
        }
        else if (this->position.y >= windowHeight) {
            this->velocity.y = -this->velocity.y;
            this->position.y = windowHeight;
        }
    }
    return this->position;
}

void Ball::reset(glm::vec2 position, glm::vec2 velocity){
    this->position = position;
    this->velocity = velocity;
    this->stuck = true;
}