#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include "../../Engine/Window/Window.h"

#include <string>

class TimeManager {
public:
	TimeManager();
	void update();

	void displayFPS(Window& window);

	int nbFrames = 0;
	float deltaTime = 0.0f;
	double lastTime = 0.0;
	double currentTime = 0.0;
	double fpsLastTime = 0.0;

	class stopwatch {
	public:
		inline void start() { startTime = glfwGetTime(); };
		inline void stop() { endTime = glfwGetTime(); };
		inline double getElapsedTime() { return endTime - startTime; };
	private:
		double startTime = 0.0;
		double endTime = 0.0;
	};
};

#endif // !TIMEMANAGER_H