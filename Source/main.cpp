/*
    KEY_ESCAPE = exit;
    KEY_F1 = wireframe mode;
*/

#include "../Engine/Window/Window.h"
#include "../Engine/Input/Input.h"
#include "../Engine/Renderer/Renderer.h"

#include <iostream>

const int width = 800, height = 600;

int main() {
    Window window(width, height, "Relay Engine");
    window.noResize(true);
    window.create();

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    Input input(width, height, window.getWindow());

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

    ColorRGB color(1.0f, 1.0f, 0.0f);

    // not working yet
    std::optional<Texture> texture = std::nullopt; //std::make_optional<Texture>("Source/Textures/tex0.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE)
    Mesh mesh(vertices, indices, color, texture);

    renderer.addMeshToRenderQueue(&mesh);

    Renderer::vSync(false);

    while (!window.shouldClose()) {
        double currentTime = glfwGetTime();
        nbFrames++;

        // FPS
        if (currentTime - lastTime >= 1.0) {
            double fps = double(nbFrames) / (currentTime - lastTime);

            std::string newTitle = "Relay Engine | FPS: " + std::to_string(static_cast<int>(fps));
            window.setTitle(newTitle.c_str());

            nbFrames = 0;
            lastTime = currentTime;
        }

        // INPUT PROCESSING
        input.processInput();

        // RENDERING
        Renderer::clearBuffers();
        renderer.drawQueuedMeshes();

        window.swapBuffers();
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}