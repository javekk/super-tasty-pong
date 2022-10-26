#include "Particle.hpp"

Particle::Particle(): 
    position(glm::vec2(0.0f))
    , velocity(glm::vec2(0.0f))
    , color(glm::vec4(1.0f))
    , life(0.0f)
{ }

Particle::Particle(
    glm::vec2 position
    , glm::vec2 velocity
    , glm::vec4 color
    , float life
): 
    position(position)
    , velocity(velocity)
    , color(color)
    , life(life)
{ }

Particle::~Particle(){ }
