#include "Game.hpp"
#include <iostream>

#include "service/resource/ResourceService.hpp"

Game::Game(unsigned int width, unsigned int height) : 
    state(GAME_ACTIVE)
    , keys()
    , width(width)
    , height(height)
    {

    std::cout << "Game constructor called:"
        << " Width: " << this->width 
        << " Height: " << this->height
        << std::endl;
}

Game::~Game(){
    std::cout << "Game de-constructor called" << std::endl;
}

void Game::init(){
    std::cout << "Game init called" << std::endl;

    ResourceService::loadShader(
        "vertex.glsl"
        , "fragment.glsl"
        , nullptr
        , "sprite"
    );
    
    // configure shaders
    glm::mat4 projection = glm::ortho(
        0.0f
        , static_cast<float>(this->width)
        , static_cast<float>(this->height)
        , 0.0f
        , -1.0f
        , 1.0f
    );

    ResourceService::getShader("sprite").use().setInt("image", 0);
    ResourceService::getShader("sprite").setMatrix4("projection", projection);
    Shader shader = ResourceService::getShader("sprite");
    renderer = new SpriteRenderer(shader);
    // load textures
    ResourceService::loadTexture("awesomeface.png", "face");
}

void Game::update(float deltaTime){
}

void Game::processInput(float deltaTime){
}

void Game::render(){
    Texture texture = ResourceService::getTexture("face");
    this->renderer->drawSprite(
        texture
        , glm::vec2(200.0f, 200.0f)
        , 0.0f
        , glm::vec2(300.0f, 400.0f)
        , glm::vec3(0.0f, 1.0f, 0.0f)
    );
}