#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <glfw3.h>

class TimeManager {
public:
	void init();
	void update();

	int nbFrames = 0;
	double lastTime = 0.0;
	double currentTime = 0.0;
	float deltaTime = 0.0f;

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
