#include "Window.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const char* title) : w(width), h(height), t(title), window(nullptr) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Window::~Window() {
    glfwTerminate();
}

void Window::create() {
    window = glfwCreateWindow(w, h, t, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    setFramebufferSizeCallback();
}

void Window::setFramebufferSizeCallback(bool useCallback) {
    if (useCallback) {
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }
    else {
        glfwSetFramebufferSizeCallback(window, NULL);
        glViewport(0, 0, w, h);
    }
}