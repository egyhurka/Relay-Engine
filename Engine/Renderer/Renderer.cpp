#include "Renderer.h"

#include <optional>

Renderer::Renderer(Camera* camera) : window(nullptr), camera(camera), shader(nullptr), time(nullptr), width(0), height(0) {
	nPlane = camera->getNearPlane();
	fPlane = camera->getFarPlane();
}

Renderer::~Renderer() {
	delete shader;
}

void Renderer::init(TimeManager* time) {
	window = glfwGetCurrentContext();
	time = time;

	glfwGetWindowSize(window, &width, &height);

	// OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);

	// BACK_FACE RENDERING
	if (backFaceRendering) {
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}
	else {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// OPENGL OPTIONS END

	loadShader();
}

void Renderer::addMeshToRenderQueue(Mesh* mesh) {
	renderQueue.push_back(mesh);
}

void Renderer::addInstancedObjectToRenderQueue(InstancedObject* object) {
	instancedQueue.push_back(object);
}

void Renderer::drawQueuedMeshes() {
	useShader();
	if (renderQueue.size() >= 1) {
		for (Mesh* mesh : renderQueue) {
			//e->rotate(20.0f, time->deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
			//e->scale(1.5f);
			shader->setBool("isInstanced", false);
			mesh->draw(shader);
		}
	}

	if (instancedQueue.size() >= 1) {
		for (InstancedObject* object : instancedQueue) {
			shader->setBool("isInstanced", true);
			object->draw(shader);
		}
	}
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

void Renderer::updateUniforms(){
	glm::mat4 projection = glm::perspective(glm::radians(camera->zoom), (float)width / (float)height, nPlane, fPlane);;
	shader->setMat4("projection", projection);

	camera->lookAt(camera->position + camera->front);
	glm::mat4 view = camera->getViewMatrix();
	shader->setMat4("view", view);
}