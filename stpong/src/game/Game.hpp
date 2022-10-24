#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "IO/sprite/SpriteRenderer.hpp"
#include "GameObject.hpp"
#include "Ball.hpp"
#include "collision.hpp"


enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
}; 


const glm::vec2 PADDLE_SIZE(30.0f, 200.0f);
const float PADDLE_VELOCITY(500.0f);
const float PADDLE_WALL_DISTANCE(PADDLE_SIZE.x + 5.0f);

const float BALL_RADIUS = 12.5f;
const float BALL_VELOCITY_MAGNITUDE = 500;

class Game{

    public:
        GameState state;	
        bool keys[1024];
        unsigned int width, height;

        Game(unsigned int width, unsigned int height);
        ~Game();

        void init();

        void processInput(float deltaTime);
        void update(float deltaTime);
        void render();

        void doCollisions();
    
    private:
        SpriteRenderer *renderer;
        GameObject *lPaddle;
        GameObject *rPaddle;
        Ball *ball;

        Collision checkCollision(Ball &ball, GameObject &paddle);
};

#endif