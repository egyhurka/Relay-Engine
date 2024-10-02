#include "Renderer.h"

#include <optional>

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
			shader->use();
			std::optional<Texture> texture = e->getTexture();
			if (texture.has_value()) {
				texture.value().texUnit(shader, "tex0", 0);
				texture.value().bind();
			}
			else {
				ColorRGB color = e->getColor();
				shader->setColor(color);
			}
			e->draw();
		}
	}
}

void Renderer::vSync(int interval) {
	glfwSwapInterval(interval);
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
