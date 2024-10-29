#ifndef INSTANCEDOBJECTDISTRIBUTOR_H
#define INSTANCEDOBJECTDISTRIBUTOR_H

#include "../Renderer/Renderer.h"
#include "../Mesh/Mesh.h"

#include <random>

enum Shape {
	CUBE,
	SPHERE,
	TRIANGLE
};

enum Distribution {
	CONTINUOUS,
	OUT_TO_IN,
	IN_TO_OUT
};

enum ColoringMethod {
	STATIC,
	DOUBLE_OUT_TO_IN,
	DOUBLE_IN_TO_OUT
};

class InstancedObjectDistributor {
public:
	InstancedObjectDistributor(Mesh* mesh,
								Renderer* renderer,
								Shape shape,
								Distribution distribution,
								unsigned long int objectCount,
								long long int seed,
								ColorRGB color1,
								std::optional<ColorRGB> color2,
								float fadeFactor,
								float scale,
								glm::vec2 volume);
private:
	Shape shape;
	glm::vec2 volume;
	glm::vec3 minVolume;
	glm::vec3 maxVolume;
	std::unique_ptr<InstancedObject> instancedObject;

	bool isPointInShape(const glm::vec3 point);
};

#endif // !INSTANCEDOBJECTDISTRIBUTOR_H
