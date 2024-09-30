#include "Input.h"

double Input::lastX = 0.0;
double Input::lastY = 0.0;
bool Input::firstMouse = true;

void Input::init(double width, double height) {
	lastX = width / 2.0;
	lastY = height / 2.0;
}

void Input::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void Input::setMouseCallbacks(GLFWwindow* window) {
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		lastX = xpos;
		lastY = ypos;
	});
}

double Input::getMouseX() {
	return lastX;
}

double Input::getMouseY() {
	return lastY;
}
