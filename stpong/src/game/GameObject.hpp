#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>


#include "IO/sprite/SpriteRenderer.hpp"
#include "IO/texture/Texture.hpp"

class GameObject{

    public:

        glm::vec2 position, size, velocity;
        glm::vec3 color;
        float rotation;
        
        Texture sprite;	

        GameObject();
        GameObject(
            glm::vec2 position
            , glm::vec2 size
            , Texture sprite
            , glm::vec3 color = glm::vec3(1.0f)
            , glm::vec2 velocity = glm::vec2(0.0f, 0.0f)
        );

        virtual void draw(SpriteRenderer &renderer);
};

#endif