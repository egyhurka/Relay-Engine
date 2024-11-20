#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <glfw3.h>

#include <string>

#include "../Camera/Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Window {
public:
	Window(unsigned int width,unsigned int height, std::string title, Camera* camera);
	~Window();

	void captureMouse(bool capture = true);
	void appendTitle(std::string title);

	inline void setTitle(std::string title) { glfwSetWindowTitle(window, title.c_str()); };
	inline void noResize(bool enabled) { glfwWindowHint(GLFW_RESIZABLE, enabled ? GLFW_FALSE : GLFW_TRUE); };
	inline void swapBuffers() const { glfwSwapBuffers(window); };

	inline GLFWwindow* getWindow() const { return window; };
	inline const glm::vec2 getWindowSize() const { return glm::vec2(width, height); };
	inline bool shouldClose() const { return glfwWindowShouldClose(window); };

	void mouse_callback(double xpos, double ypos);
	void scroll_callback(double xoffset, double yoffset);
private:
	GLFWwindow* window;
	Camera* camera;
	std::string title;
	unsigned int width, height;
	float lastX, lastY;

	static void mouseCallbackDispatcher(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallbackDispatcher(GLFWwindow* window, double xoffset, double yoffset);

	void setCallbacks();
};


#endif // !WINDOW_H