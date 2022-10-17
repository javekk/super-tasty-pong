
#include "GameObject.hpp"


GameObject::GameObject(): 
    position(0.0f, 0.0f)
    , size(1.0f, 1.0f)
    , velocity(0.0f)
    , color(1.0f)
    , rotation(0.0f)
    , sprite(){ }


GameObject::GameObject(
    glm::vec2 position
    , glm::vec2 size
    , Texture sprite
    , glm::vec3 color
    , glm::vec2 velocity
) : 
    position(position)
    , size(size)
    , velocity(velocity)
    , color(color)
    , rotation(0.0f)
    , sprite(sprite) { }


void GameObject::draw(SpriteRenderer &renderer){
    renderer.drawSprite(
        this->sprite
        , this->position
        , this->rotation
        , this->size
        , this->color
    );
}
