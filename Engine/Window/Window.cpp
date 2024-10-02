#include "Window.h"

#include <iostream>

const char* glfwError = "ERROR::GLFW::";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const char* title) : w(width), h(height), t(title), window(nullptr) {
    if (!glfwInit()) {
        std::cerr << glfwError << "FAILED_TO_INIT_GLFW" << std::endl;
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
        std::cerr << glfwError << "FAILED_TO_CREATE_GLFW_WINDOW" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "ERROR::GLAD::FAILED_TO_INIT_GLAD" << std::endl;
        return;
    }

    setFramebufferSizeCallback();
}

void Window::setTitle(const char* title) {
    glfwSetWindowTitle(window, title);
}

void Window::noResize(bool enabled) {
    glfwWindowHint(GLFW_RESIZABLE, enabled ? GLFW_FALSE : GLFW_TRUE);
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