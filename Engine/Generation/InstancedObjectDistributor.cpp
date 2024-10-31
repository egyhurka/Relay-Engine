#include "InstancedObjectDistributor.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/constants.hpp"
#include <cmath>

InstancedObjectDistributor::InstancedObjectDistributor(Mesh* mesh, Renderer* renderer, Shape shape, Distribution distribution, unsigned long int objectCount, long long int seed, ColorRGB color1, std::optional<ColorRGB> color2, float fadeFactor, float scale, glm::vec2 volume) {
	this->shape = shape;
	this->volume = volume;
	minVolume = glm::vec3(volume.x);
	maxVolume = glm::vec3(volume.y);
	
	std::mt19937 generator(static_cast<unsigned int>(seed));

	std::uniform_real_distribution<> dist(this->volume.x, this->volume.y);
	
	mesh->setColor({ 0.0f, 0.0f, 0.0f });
	mesh->isTransparent = true;
	renderer->addMeshToRenderQueue(mesh);
	instancedObject = std::make_unique<InstancedObject>(mesh);

	Loader::batch(objectCount, Loader::batchSizeCalculator(objectCount), true, [&](int i) {
		glm::vec3 position;
		do {
			position = { dist(generator), dist(generator), dist(generator) };
		} while (!isPointInShape(position));
		instancedObject->addInstancePosition(position);
	});

	if (!color2.has_value()) {
		instancedObject->addInstanceColor(color1);
		instancedObject->isMonochromatic = true;
	}

	instancedObject->setupInstances();
	renderer->addInstancedObjectToRenderQueue(instancedObject.get());
}

bool InstancedObjectDistributor::isPointInShape(const glm::vec3 point) {
	switch (shape) {
		case CUBE:
			return (point.x >= minVolume.x && point.x <= maxVolume.x) &&
					(point.y >= minVolume.y && point.y <= maxVolume.y) &&
					(point.z >= minVolume.z && point.z <= maxVolume.z);
		case SPHERE:
			return glm::distance(point, glm::vec3(0)) <= std::abs(volume.x);
		case TRIANGLE:
			return false;
		default:
			return false;
	}
}