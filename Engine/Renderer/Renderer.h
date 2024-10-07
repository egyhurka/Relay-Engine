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
#include "../../Utilities/Time/TimeManager.h"

class Renderer {
public:
	Renderer(Camera* camera);
	~Renderer();

	void init(TimeManager* time);
	void addMeshToRenderQueue(Mesh* mesh);
	void removeMeshFromRenderQueue(Mesh* mesh);
	void drawQueuedMeshes();

	static void vSync(bool interval);
	static void polygonMode(GLenum mode);
	static void clearBuffers();
private:
	Shader* shader;
	Camera* camera;
	GLFWwindow* window;
	TimeManager* time;
	std::vector<Mesh*> renderQueue;

	int width, height;

	void loadShader();
	void useShader();
	void updateUniforms(Mesh* e);
};

#endif // !RENDERER_H
