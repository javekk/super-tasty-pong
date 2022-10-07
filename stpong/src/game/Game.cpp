#include "Game.hpp"
#include <iostream>


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
    std::cout << "Game de-constructor called"
        << std::endl;
}

void Game::init(){
   std::cout << "Game init called"
        << std::endl;
}

void Game::update(float deltaTime){
}

void Game::processInput(float deltaTime){
}

void Game::render(){
    
}