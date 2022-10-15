#include "Game.hpp"
#include <iostream>

#include "service/resource/ResourceService.hpp"

Game::Game(unsigned int width, unsigned int height): 
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

    ResourceService::loadTexture("background.jpg", "background");
    ResourceService::loadTexture("paddle_1.jpg", "rPaddle");
    ResourceService::loadTexture("paddle_2.jpg", "lPaddle");
    Texture rPaddleTexture = ResourceService::getTexture("rPaddle");
    Texture lPaddleTexture = ResourceService::getTexture("lPaddle");

    glm::vec2 rPaddlePos = glm::vec2(
        PADDLE_WALL_DISTANCE
        , this-> height / 2.0f - PADDLE_SIZE.y / 2.0f
    );
    this->rPaddle = new GameObject(rPaddlePos, PADDLE_SIZE, rPaddleTexture);
    glm::vec2 lPaddlePos = glm::vec2(
        this->width - PADDLE_WALL_DISTANCE - PADDLE_SIZE.x
        , this-> height / 2.0f - PADDLE_SIZE.y / 2.0f
    );
    this->lPaddle = new GameObject(lPaddlePos, PADDLE_SIZE, lPaddleTexture);
}

void Game::update(float deltaTime){
}

void Game::processInput(float deltaTime){
}

void Game::render(){
    Texture background = ResourceService::getTexture("background");
    this->renderer->drawSprite(
        background
        , glm::vec2(0.0f, 0.0f)
        , 0.0f
        , glm::vec2(this->width, this->height)
    );

    this->rPaddle->draw(*this->renderer);
    this->lPaddle->draw(*this->renderer);
}