#ifndef RANDOM_H

#include <glm.hpp>

#include "../../Utilities/Color.h"

#include <random>

class Random {
public:
    Random(glm::vec2 volume);

    glm::vec3 randomPosition();
    ColorRGB randomColor();

private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> disX;
    std::uniform_real_distribution<> disY;
    std::uniform_real_distribution<> disZ;
};

#endif // !RANDOM_H
