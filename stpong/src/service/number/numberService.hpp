#ifndef NUMBERSERVICE_HPP
#define NUMBERSERVICE_HPP
#pragma once

#include <glm/glm.hpp>


int getRandomNumber(int lowerBound, int upperBound);

int assignRandomSign(int value);

glm::vec2 getInitialVelocity(int magnitude);


#endif