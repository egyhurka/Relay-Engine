#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>

#include <vector>

#include "Shader/Shader.h"
#include "../Mesh/Mesh.h"

class Renderer {
public:
	~Renderer();
	void init();
	void addMeshToRenderQueue(Mesh* mesh);
	void removeMeshFromRenderQueue(Mesh* mesh);
	void drawQueuedMeshes();
	static void vsync(bool enabled, std::optional<int> target);
	static void clearBuffers();
private:
	void loadShader();
	void useShader();
	Shader* shader;
	std::vector<Mesh*> renderQueue;
};

#endif // !RENDERER_H
