#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <glm/glm.hpp>

class Particle{

    public:
        glm::vec2 position, velocity;
        glm::vec4 color;
        float life;

        Particle();
        Particle(
            glm::vec2 position
            , glm::vec2 velocity
            , glm::vec4 color
            , float life
        );
        ~Particle();
};
#endif