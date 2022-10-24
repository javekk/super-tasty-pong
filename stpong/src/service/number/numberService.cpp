#include "numberService.hpp"
#include <random>
#include <cmath>
#include <iostream>

int getRandomNumber(int lowerBound, int upperBound){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(lowerBound, upperBound);
    return distribution(mt); 
}

int assignRandomSign(int value){
    return getRandomNumber(0,1) == 0 ? value : -value;
}

glm::vec2 getInitialVelocity(int magnitude){
    int _xArea = magnitude / 4;
    int x = getRandomNumber(2*_xArea, 3*_xArea);
    int y = sqrt(pow(magnitude,2) - pow(x,2));
    glm::vec2 velocity(assignRandomSign(x), assignRandomSign(y));
    return velocity;
}

