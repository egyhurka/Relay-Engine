#include "TimeManager.h"

void TimeManager::init() {
	nbFrames = 0;
	lastTime = glfwGetTime();
	deltaTime = 0.0f;
	currentTime = lastTime;
}

void TimeManager::update() {
	currentTime = glfwGetTime();
	deltaTime = static_cast<float>(currentTime - lastTime);
	lastTime = currentTime;
}