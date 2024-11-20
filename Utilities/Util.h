#ifndef UTIL_H
#define UTIL_H

#include <glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 color = glm::vec3(0.0f);
	glm::vec3 normal = glm::vec3(0.0f);
};

#endif // !UTIL_H
