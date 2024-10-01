#include "../Engine/Window/Window.h"
#include "../Engine/Input/Input.h"
#include "../Engine/Renderer/Renderer.h"

#include <iostream>

int main() {
    Window window(800, 600, "Relay Engine");
    window.create();

    Vec2i windowSize = window.getWindowSize();
    Input::init((double)windowSize.x, (double)windowSize.y);

    Renderer renderer;
    renderer.init();

    std::vector<GLfloat> vertices = {
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    std::vector<GLuint> indices = {
        0, 1, 2
    };

    ColorRGB color(1.0f, 0.5f, 0.2f);
    std::optional<Texture> texture = std::nullopt;
    Mesh mesh(vertices, indices, color, texture);

    renderer.addMeshToRenderQueue(&mesh);

    Renderer::vsync(false, std::nullopt);
    glEnable(GL_DEPTH_TEST);

    while (!window.shouldClose()) {
        // INPUT PROCESSING
        Input::processInput(window.getWindow());

        // RENDERING
        Renderer::clearBuffers();
        renderer.drawQueuedMeshes();

        window.swapBuffers();
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}