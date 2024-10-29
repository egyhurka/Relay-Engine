#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <glfw3.h>
#include <glm.hpp>

class Window {
public:
	Window(unsigned int width,unsigned int height, const char* title);
	~Window();

	void setFramebufferSizeCallback(bool useCallback = false);
	void captureMouse(bool capture = true);
	void setTitle(const char* title);

	inline void noResize(bool enabled) { glfwWindowHint(GLFW_RESIZABLE, enabled ? GLFW_FALSE : GLFW_TRUE); };
	inline void swapBuffers() const { glfwSwapBuffers(window); };
	inline GLFWwindow* getWindow() const { return window; };
	inline const glm::vec2 getWindowSize() const { return glm::vec2(w, h); };
	inline bool shouldClose() const { return glfwWindowShouldClose(window); };
private:
	GLFWwindow* window;
	int w, h;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif // !WINDOW_H