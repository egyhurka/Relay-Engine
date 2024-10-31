#include "Window.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

const char* glfwError = "ERROR::GLFW::";
bool firstMouse = true;

Window::Window(unsigned int width,unsigned int height, std::string title, Camera* camera) : width(width), height(height), title(title), window(nullptr), camera(camera), lastX(width / 2.0f), lastY(height / 2.0f) {
    if (!glfwInit()) {
        std::cerr << glfwError << "FAILED_TO_INIT_GLFW" << std::endl;
        return;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    // CREATE WINDOW
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
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

    // CALLBACKS
    setCallbacks();

    std::cout << "ENGINE::WINDOW::SUCCESSFULLY_CREATED" << std::endl;
}

Window::~Window() {
    glfwTerminate();
}

void Window::captureMouse(bool capture) {
    if (capture) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void Window::appendTitle(std::string title) {
    std::string newTitle = this->title;
    newTitle += " | " + title;
    setTitle(newTitle);
}

void Window::mouse_callback(double xpos, double ypos) {
    float fx = static_cast<float>(xpos);
    float fy = static_cast<float>(ypos);

    if (firstMouse) {
        lastX = fx;
        lastY = fy;
        firstMouse = false;
    }

    float xoffset = fx - lastX;
    float yoffset = lastY - fy;

    lastX = fx;
    lastY = fy;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

void Window::scroll_callback(double xoffset, double yoffset) {
    camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void Window::mouseCallbackDispatcher(GLFWwindow* window, double xpos, double ypos) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (win)
        win->mouse_callback(xpos, ypos);
}

void Window::scrollCallbackDispatcher(GLFWwindow* window, double xoffset, double yoffset) {
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (win)
        win->scroll_callback(xoffset, yoffset);
}

void Window::setCallbacks() {
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, Window::mouseCallbackDispatcher);
    glfwSetScrollCallback(window, Window::scrollCallbackDispatcher);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}