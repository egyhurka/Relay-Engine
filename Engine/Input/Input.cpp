#include "Input.h"

bool wireframeMode = false, isF1Pressed = false;

Input::Input(int width, int height, GLFWwindow* window) : width(width), height(height), window(window) {
	
}

void Input::processInput() {
	if (getKey(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}

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
}

bool Input::getKey(int key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}
