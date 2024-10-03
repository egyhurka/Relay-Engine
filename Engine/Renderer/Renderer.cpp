#include "Renderer.h"

#include <optional>

Renderer::~Renderer() {
	delete shader;
}

void Renderer::init() {
	// OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// OPENGL OPTIONS END

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

void Renderer::vSync(bool interval) {
	glfwSwapInterval(interval);
}

void Renderer::polygonMode(GLenum mode) {
	if (mode == GL_FILL || mode == GL_LINE) {
		glPolygonMode(GL_FRONT_AND_BACK, mode);
	}
	else {
		std::cerr << "ERROR::RENDERER::INVALID_POLYGON_MODE" << std::endl;
	}
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
