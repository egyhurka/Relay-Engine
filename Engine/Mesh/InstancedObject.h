#ifndef INSTANCEDOBJECT_H
#define INSTANCEDOBJECT_H

#include "Mesh.h"

class Mesh;

class InstancedObject {
public:	
	InstancedObject(Mesh* mesh);
	~InstancedObject();

	void addInstancePosition(const glm::vec3& position);
	void addInstanceColor(const ColorRGB color);
	void setupInstances();
	void draw(Shader* shader);

	bool isMonochromatic = false;
private:
	Mesh* mesh;
	std::vector<glm::vec3> instancedPositions;
	std::vector<ColorRGB> instancedColors;
	GLuint instanceVBO, instanceColorVBO;
};

#endif // !INSTANCEDOBJECT_H
