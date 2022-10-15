#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GameObject.hpp"
#include "IO/sprite/SpriteRenderer.hpp"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
}; 


const glm::vec2 PADDLE_SIZE(30.0f, 200.0f);
const float PADDLE_VELOCITY(500.0f);
const float PADDLE_WALL_DISTANCE(PADDLE_SIZE.x + 5.0f);


class Game{

    public:
        GameState    state;	
        bool         keys[1024];
        unsigned int width, height;

        Game(unsigned int width, unsigned int height);
        ~Game();

        void init();

        // Game loop
        void processInput(float deltaTime);
        void update(float deltaTime);
        void render();
    
    private:
        SpriteRenderer *renderer;
        GameObject *rPaddle;
        GameObject *lPaddle;
};

#endif