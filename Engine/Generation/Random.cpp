#include "Random.h"

Random::Random(glm::vec2 volume) : disX(volume.x, volume.y), disY(volume.x, volume.y), disZ(volume.x, volume.y) {}

glm::vec3 Random::randomPosition() {
    return glm::vec3(disX(gen), disY(gen), disZ(gen));
}

ColorRGB Random::randomColor() {
    return ColorRGB(disX(gen), disY(gen), disZ(gen));
}
