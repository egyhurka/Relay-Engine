#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <vector>

#include "Shader/Shader.h"
#include "../Mesh/Mesh.h"
#include "../Camera/Camera.h"

class Renderer {
public:
	Renderer(Camera* camera);
	~Renderer();
	void init();
	void addMeshToRenderQueue(Mesh* mesh);
	void removeMeshFromRenderQueue(Mesh* mesh);
	void drawQueuedMeshes();
	static void vSync(bool interval);
	static void polygonMode(GLenum mode);
	static void clearBuffers();
private:
	void loadShader();
	void useShader();
	Shader* shader;
	Camera* camera;
	std::vector<Mesh*> renderQueue;
};

#endif // !RENDERER_H
