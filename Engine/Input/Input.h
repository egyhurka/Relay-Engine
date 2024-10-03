#ifndef INPUT_H
#define INPUT_H

#include <glfw3.h>
#include <iostream>

class Input {
public:
	Input(int width, int height, GLFWwindow* window);
	void processInput();
private:
	bool getKey(int key);
	GLFWwindow* window;
	int width, height;
};

#endif // !INPUT_H
