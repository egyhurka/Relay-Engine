#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <glfw3.h>

#include "../../Utilities/Vector2.h"

class Window {
public:
	Window(int width, int height, const char* title);
	~Window();
	void create();
	void setTitle(const char* title);
	void noResize(bool enabled);
	void setFramebufferSizeCallback(bool useCallback = false);
	void captureMouse(bool capture = true);
	void swapBuffers() const { glfwSwapBuffers(window); };
	GLFWwindow* getWindow() const { return window; }
	bool shouldClose() const { return glfwWindowShouldClose(window); }
	Vec2i getWindowSize() const { return Vec2i(w, h); };
private:
	GLFWwindow* window;
	int w, h;
	const char* t;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif // !WINDOW_H