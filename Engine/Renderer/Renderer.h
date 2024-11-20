#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <vector>

#include "Shader/Shader.h"
#include "Loader.h"
#include "../Mesh/Mesh.h"
#include "../Camera/Camera.h"
#include "../../Utilities/Time/TimeManager.h"

class Renderer {
public:
	Renderer(Camera* camera);
	~Renderer();

	void init(TimeManager* time);
	void addMeshToRenderQueue(Mesh* mesh);
	void addInstancedObjectToRenderQueue(InstancedObject* object);
	void drawQueuedMeshes();
	void updateUniforms();
	
	inline Shader* getShader() const { return shader; };
	inline void setBackFaceRendering(bool value) { backFaceRendering = value; };
	
	static inline void vSync(bool interval = false) { glfwSwapInterval(interval); };
	static inline void setBackgroundColor(ColorRGBA color) { glClearColor(color.r, color.g, color.b, color.a); };
	static inline void clearBuffers() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); };

	static void polygonMode(GLenum mode);
private:
	Shader* shader;
	Camera* camera;
	GLFWwindow* window;
	TimeManager* time;
	std::vector<Mesh*> renderQueue;
	std::vector<InstancedObject*> instancedQueue;

	int width, height;
	float nPlane, fPlane;
	bool backFaceRendering = false;

	void loadShader();
	void useShader();
};

#endif // !RENDERER_H
