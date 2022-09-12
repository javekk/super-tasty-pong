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

        GameState    State;	
        bool         Keys[1024];
        unsigned int Width, Height;

        Game(unsigned int width, unsigned int height);
        ~Game();

        void init();

        // Game loop
        void processInput(float dt);
        void update(float dt);
        void render();
};

#endif