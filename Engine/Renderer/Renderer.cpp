#include "Renderer.h"

#include <optional>

bool backFaceRendering = false;

Renderer::Renderer(Camera* camera) : window(nullptr), camera(camera), shader(nullptr), time(nullptr), width(0), height(0) {}

Renderer::~Renderer() {
	delete shader;
}

void Renderer::init(TimeManager* time) {
	this->window = glfwGetCurrentContext();
	this->time = time;

	glfwGetWindowSize(window, &width, &height);

	// OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);

	// BACK_FACE RENDERING
	if (backFaceRendering) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);	
	}

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
	if (!renderQueue.empty()) {
		for (Mesh* e : renderQueue) {
			useShader();

			//e->rotate(20.0f, time->deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));

			updateUniforms(e);

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
	shader = new Shader("Engine/Renderer/Shader/vertex/shader.vert", "Engine/Renderer/Shader/fragment/shader.frag");
}

void Renderer::useShader() {
	shader->use();
}

void Renderer::updateUniforms(Mesh* e) {
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)width / (float)height, 0.1f, 200.0f);;
	shader->setMat4("projection", projection);

	glm::mat4 view = camera->getViewMatrix();
	shader->setMat4("view", view);

	glm::mat4 model = e->getModelMatrix();
	shader->setMat4("model", model);
}

void Renderer::clearBuffers() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
