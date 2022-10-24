
#include "collision.hpp"
#include "iostream"

const glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// UP
        glm::vec2(1.0f, 1.0f),	// UP_RIGHT
        glm::vec2(1.0f, 0.0f),	// RIGHT
        glm::vec2(1.0f, -1.0f),	// DOWN_RIGHT
        glm::vec2(0.0f, -1.0f),	// DOWN
        glm::vec2(-1.0f, -1.0f),// DOWN_LEFT
        glm::vec2(-1.0f, 0.0f),	// LEFT
        glm::vec2(-1.0f, 1.0f)	// UP_LEFT
    };

Collision::Collision(
    bool isACollision
    , glm::vec2 difference
) : 
    isACollision(isACollision)
    , difference(difference) {

    this->direction = this->getDirection();
}

Collision::~Collision(){ }

Direction Collision::getDirection(){

    float max = 0.0f;
    unsigned int best_match = -1;
    if(this->isACollision){
        glm::vec2 normDifference = glm::normalize(this->difference);
        for (unsigned int i = 0; i < 8; i++){
            float dot_product = glm::dot(normDifference, compass[i]);
            if (dot_product > max){
                max = dot_product;
                best_match = i;
            }
        }
        return (Direction)best_match;
    }
    return UP;
}