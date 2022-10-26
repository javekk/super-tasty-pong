#ifndef PARTICLEGENERATOR_HPP
#define PARTICLEGENERATOR_HPP

#include <vector>

#include "Particle.hpp"
#include "IO/shader/Shader.hpp"
#include "IO/texture/Texture.hpp"
#include "game/GameObject.hpp"


class ParticleGenerator{

    public:
        ParticleGenerator(
            Shader shader
            , Texture texture
            , unsigned int amount
        );

        void update(
            float dt
            , GameObject &object
            , unsigned int newParticles
            , glm::vec2 offset = glm::vec2(0.0f, 0.0f)
        );

        void draw();

    private:
        std::vector<Particle> particles;
        unsigned int amount;
        Shader shader;
        Texture texture;
        unsigned int VAO;

        void init();

        unsigned int lastUsedParticleIndex = 0;
        unsigned int firstUnusedParticle();
        void respawnParticle(
            Particle &particle
            , GameObject &object
            , glm::vec2 offset = glm::vec2(0.0f, 0.0f)
        );
};



#endif