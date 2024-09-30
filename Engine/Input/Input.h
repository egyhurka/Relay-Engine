#ifndef INPUT_H
#define INPUT_H

#include <glfw3.h>
#include <iostream>

class Input {
public:
	static void init(double width, double height);
	static void processInput(GLFWwindow* window);
	static void setMouseCallbacks(GLFWwindow* window);
	static double getMouseX();
	static double getMouseY();
private:
	static double lastX, lastY;
	static bool firstMouse;
};

#endif // !INPUT_H
