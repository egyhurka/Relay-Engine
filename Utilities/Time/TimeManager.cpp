#include "TimeManager.h"

TimeManager::TimeManager(){
	nbFrames = 0;
	lastTime = glfwGetTime();
	deltaTime = 0.0f;
	currentTime = lastTime;
}

void TimeManager::update() {
	nbFrames++;
	currentTime = glfwGetTime();
	deltaTime = static_cast<float>(currentTime - lastTime);
	lastTime = currentTime;
}

void TimeManager::displayFPS(Window& window) {
	if (currentTime - fpsLastTime >= 1.0) {
		double fps = static_cast<double>(nbFrames);
		std::string newTitle = "FPS: " + std::to_string(static_cast<int>(fps));
		window.appendTitle(newTitle);

		nbFrames = 0;
		fpsLastTime += 1.0;
	}
}