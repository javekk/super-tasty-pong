#include "Game.hpp"
#include <iostream>

#include "service/resource/ResourceService.hpp"
#include "service/number/numberService.hpp"


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
    srand(time(0)); 

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

    glm::vec2 lPaddlePos = glm::vec2(
        PADDLE_WALL_DISTANCE
        , this->height / 2.0f - PADDLE_SIZE.y / 2.0f
    );
    this->lPaddle = new GameObject(lPaddlePos, PADDLE_SIZE, rPaddleTexture);
    glm::vec2 rPaddlePos = glm::vec2(
        this->width - PADDLE_WALL_DISTANCE - PADDLE_SIZE.x
        , this->height / 2.0f - PADDLE_SIZE.y / 2.0f
    );
    this->rPaddle = new GameObject(rPaddlePos, PADDLE_SIZE, lPaddleTexture);

    glm::vec2 ballPos = glm::vec2(
        this-> width / 2.0f
        , this->height / 2.0f
    );
    ResourceService::loadTexture("awesomeface.png", "face");

    const glm::vec2 PADDLE_SIZE(-250.0f, -433.0f);
    this->ball = new Ball(
        ballPos, 
        BALL_RADIUS, 
        getInitialVelocity(BALL_VELOCITY_MAGNITUDE),
        ResourceService::getTexture("face")
    );
}

void Game::update(float deltaTime){
    this->ball->move(deltaTime, this->height);
}

void Game::processInput(float deltaTime){
    if (this->state == GAME_ACTIVE){
        float velocity = PADDLE_VELOCITY * deltaTime;

        // Left paddle
        if (this->keys[GLFW_KEY_W]){
            if (this->lPaddle->position.y >= 0.0f)
                this->lPaddle->position.y -= velocity;
        }
        if (this->keys[GLFW_KEY_S]){        
            if (this->lPaddle->position.y <= (this->height - this->rPaddle->size.y))
                this->lPaddle->position.y += velocity;
        }

        // Right paddle
        if (this->keys[GLFW_KEY_UP]){
            if (this->rPaddle->position.y >= 0.0f)
                this->rPaddle->position.y -= velocity;
        }
        if (this->keys[GLFW_KEY_DOWN]){        
            if (this->rPaddle->position.y <= (this->height - this->rPaddle->size.y))
                this->rPaddle->position.y += velocity;
        }

        // Ball
        if (this->keys[GLFW_KEY_SPACE])
            this->ball->stuck = false;
    }
}

void Game::render(){
    Texture background = ResourceService::getTexture("background");
    this->renderer->drawSprite(
        background
        , glm::vec2(0.0f, 0.0f)
        , 0.0f
        , glm::vec2(this->width, this->height)
    );

    this->lPaddle->draw(*this->renderer);
    this->rPaddle->draw(*this->renderer);
    this->ball->draw(*this->renderer);
}