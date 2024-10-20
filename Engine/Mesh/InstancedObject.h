#ifndef INSTANCEDOBJECT_H
#define INSTANCEDOBJECT_H

#include "Mesh.h"

class Mesh;

class InstancedObject {
public:	
	InstancedObject(Mesh* mesh);
	~InstancedObject();

	void addInstancePosition(const glm::vec3& position);
	void setupInstances();
	void draw(Shader* shader);
private:
	Mesh* mesh;
	std::vector<glm::vec3> instancedPositions;
	GLuint instanceVBO;
};

#endif // !INSTANCEDOBJECT_H
