#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <glfw3.h>

#include "../../Utilities/Vector2.h"

class Window {
public:
	Window(int width, int height, const char* title);
	~Window();

	void setFramebufferSizeCallback(bool useCallback = false);
	void captureMouse(bool capture = true);
	void setTitle(const char* title);

	inline void noResize(bool enabled) { glfwWindowHint(GLFW_RESIZABLE, enabled ? GLFW_FALSE : GLFW_TRUE); };
	inline void swapBuffers() const { glfwSwapBuffers(window); }
	inline GLFWwindow* getWindow() const { return window; }
	inline const Vec2i getWindowSize() const { return Vec2i(w, h); }
	inline bool shouldClose() const { return glfwWindowShouldClose(window); }
private:
	GLFWwindow* window;
	int w, h;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif // !WINDOW_H