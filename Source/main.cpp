/*
    KEY_ESCAPE = exit;
    KEY_F1 = wireframe mode;
*/

#include "../Engine/Window/Window.h"
#include "../Engine/Input/Input.h"
#include "../Engine/Renderer/Renderer.h"
#include "../Utilities/Time/TimeManager.h"

#include <iostream>
#include <random>

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const int width = 1920, height = 1080;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = width / 2.0f;
float lastY = height / 2.0f;
bool firstMouse = true;

int main() {
    Window window(width, height, "Relay Engine");
    window.noResize(true);
    window.create();
    window.captureMouse();

    glfwSetFramebufferSizeCallback(window.getWindow(), framebuffer_size_callback);
    glfwSetCursorPosCallback(window.getWindow(), mouse_callback);
    glfwSetScrollCallback(window.getWindow(), scroll_callback);
    

    Renderer renderer(&camera);
    Input input(width, height, window.getWindow(), &camera);
    TimeManager time;
    time.init();
    double fpsLastTime = time.currentTime;

    renderer.init(&time);

    //ColorRGB color(0.0f, 0.0f, 0.0f);

    // not working yet
    //std::optional<Texture> texture = std::make_optional<Texture>("Source/Textures/tex0.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);

    int numCubes = 5'000;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-30.0f, 30.0f);

    for (int i = 0; i < numCubes; ++i) {
        ColorRGB randomColor = { 1.0f, 1.0f, 1.0f};
        do {
            randomColor = ColorRGB(dis(gen), dis(gen), dis(gen));
        } while (randomColor.r == 0.0f && randomColor.g == 0.0f && randomColor.b == 0.0f);
        CubeMesh* cube = new CubeMesh(randomColor, std::nullopt);
        glm::vec3 randomPosition(dis(gen), dis(gen), dis(gen));
        cube->translate(randomPosition);
        renderer.addMeshToRenderQueue(cube);
    }

    Renderer::vSync(false);

    while (!window.shouldClose()) {
        time.update();
        time.nbFrames++;

        // FPS
        if (time.currentTime - fpsLastTime >= 1.0) {
            double fps = static_cast<double>(time.nbFrames);
            std::string newTitle = "Relay Engine | FPS: " + std::to_string(static_cast<int>(fps));
            window.setTitle(newTitle.c_str());

            time.nbFrames = 0;
            fpsLastTime += 1.0;
        }

        // INPUT PROCESSING
        input.processInput(time.deltaTime);

        // RENDERING
        Renderer::clearBuffers();
        Renderer::setBackgroundColor({0.0f, 0.0f, 0.0f, 1.0f});

        renderer.drawQueuedMeshes();

        window.swapBuffers();
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}