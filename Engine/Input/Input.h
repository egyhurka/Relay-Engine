#ifndef INPUT_H
#define INPUT_H

#include <glfw3.h>
#include <iostream>

#include "../Camera/Camera.h"

class Input {
public:
	Input(int width, int height, GLFWwindow* window, Camera* camera);

	void processInput(float deltaTime);
private:
	static bool wireframeMode;
	static bool isF1Pressed;
	bool getKey(int key);
	GLFWwindow* window;
	Camera* camera;
	int width, height;
};

#endif // !INPUT_H
