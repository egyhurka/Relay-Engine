#include "../Engine/Window/Window.h"
#include "../Engine/Input/Input.h"

#include <iostream>

int main() {
    Window window(800, 600, "Relay Engine");
    window.create();

    Vec2i windowSize = window.getWindowSize();
    Input::init((double)windowSize.x, (double)windowSize.y);

    glEnable(GL_DEPTH_TEST);

    while (!window.shouldClose()) {
        Input::processInput(window.getWindow());

        glClear(GL_COLOR_BUFFER_BIT);

        window.swapBuffers();
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}