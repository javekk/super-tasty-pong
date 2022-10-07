#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>


enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
}; 

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
};

#endif