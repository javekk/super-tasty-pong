#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include "IO/shader/Shader.hpp"
#include "IO/texture/Texture.hpp"

class SpriteRenderer{

    public:
        SpriteRenderer(Shader &shader);
        ~SpriteRenderer();

        void drawSprite(
            Texture &texture
            , glm::vec2 position
            , float rotate = 0.0f
            , glm::vec2 size = glm::vec2(10.0f, 10.0f)
            , glm::vec3 color = glm::vec3(1.0f)
        );

    private:
        Shader shader; 
        unsigned int VAO;

        void initRenderData();
};


#endif