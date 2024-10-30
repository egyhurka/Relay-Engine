#include "Input.h"

bool Input::wireframeMode = false;
bool Input::isF1Pressed = false;

Input::Input(int width, int height, GLFWwindow* window, Camera* camera) : width(width), height(height), window(window), camera(camera) {}

void Input::processInput(float deltaTime) {
	// CLOSE WINDOW
	if (getKey(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}

	// WIREFRAME MODE
	if (getKey(GLFW_KEY_F1)) {
		if (!isF1Pressed) {
			wireframeMode = !wireframeMode;
			glPolygonMode(GL_FRONT_AND_BACK, wireframeMode ? GL_FILL : GL_LINE);
			isF1Pressed = true;
		}
	}
	else {
		isF1Pressed = false;
	}

	// CAMERA MOVEMENT
	if (getKey(GLFW_KEY_W))
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (getKey(GLFW_KEY_S))
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (getKey(GLFW_KEY_A))
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (getKey(GLFW_KEY_D))
		camera->ProcessKeyboard(RIGHT, deltaTime);
	if (getKey(GLFW_KEY_E))
		camera->ProcessKeyboard(UP, deltaTime);
	if (getKey(GLFW_KEY_Q))
		camera->ProcessKeyboard(DOWN, deltaTime);

	if (getKey(GLFW_KEY_LEFT_SHIFT)) {
		camera->setMovementSpeedMultiplier(5);
	}
	else {
		camera->setMovementSpeedMultiplier();
	}

	// CAMERA MOVEMENT END
}

bool Input::getKey(int key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}
