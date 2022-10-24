#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <glm/glm.hpp>


enum Direction {
	UP,
    UP_RIGHT,
	RIGHT,
    DOWN_RIGHT,
	DOWN,
    DOWN_LEFT,
	LEFT,
    UP_LEFT,
};   


class Collision{
    public:
        bool isACollision;
        Direction direction;
        glm::vec2 difference;

        Collision(
            bool isACollision
            , glm::vec2 difference
        );
        ~Collision();
    
    private:
        Direction getDirection(); 
};


 


#endif