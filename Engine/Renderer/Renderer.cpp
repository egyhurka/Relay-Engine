#include "Renderer.h"

#include <algorithm>

Renderer::~Renderer() {
	delete shader;
}

void Renderer::init() {
	loadShader();
}

void Renderer::addMeshToRenderQueue(Mesh* mesh) {
	renderQueue.push_back(mesh);
}

void Renderer::removeMeshFromRenderQueue(Mesh* mesh) {
	// ---
}

void Renderer::drawQueuedMeshes() {
	useShader();
	if (renderQueue.size() > 0) {
		for (Mesh* e : renderQueue) {
			e->draw();
		}
	}
}

void Renderer::vsync(bool enabled, std::optional<int> target) {
	glfwSwapInterval(enabled ? target.value_or(1) : 0);
}

void Renderer::loadShader() {
	shader = new Shader("Engine/Renderer/Shader/vertex/shader.vert",
						"Engine/Renderer/Shader/fragment/shader.frag");
}

void Renderer::useShader() {
	shader->use();
}

void Renderer::clearBuffers() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
