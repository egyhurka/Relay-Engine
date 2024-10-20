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

const int width = 800, height = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = width / 2.0f;
float lastY = height / 2.0f;
bool firstMouse = true;

int main() {
    Window window(width, height, "Relay Engine");
    window.noResize(true);
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

    const int totalCubes = 1'000'000;
    const int batchSize = 1000;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-300.0f, 300.0f);

    ColorRGB color = { 0.2f, 0.2f, 1.0f };

    InstancedObject* instancedObject = new InstancedObject(new CubeMesh(color, std::nullopt));

    for (int i = 0; i < totalCubes; i += batchSize) {
        for (int j = 0; j < batchSize && (i + j) < totalCubes; ++j) {
            glm::vec3 randomPosition(dis(gen), dis(gen), dis(gen));
            instancedObject->addInstancePosition(randomPosition);
        }
        std::cout << "ENGINE::INSTANCES::LOADED " << std::min(i + batchSize, totalCubes) << " OUT OF " << totalCubes << std::endl;
    }

    instancedObject->setupInstances();
    renderer.addInstancedObjectToRenderQueue(instancedObject);

    /*ColorRGB color2 = {0.0f, 0.3f, 1.0f};
    for (int i = 0; i < 1; ++i) {
        CubeMesh* cube = new CubeMesh(color2, std::nullopt);
        glm::vec3 randomPosition(dis(gen), dis(gen), dis(gen));
        cube->translate(randomPosition);
        renderer.addMeshToRenderQueue(cube);
    }*/

    // NOT WORKING WITHOUT THIS
    ColorRGB testColor = { 0.0f, 1.0f, 0.0f };
    CubeMesh* testCube = new CubeMesh(testColor, std::nullopt);
    renderer.addMeshToRenderQueue(testCube);

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

    std::cout << "ENGINE::CLEANUP::PROGRESS" << std::endl;
    renderer.cleanUp();
    std::cout << "ENGINE::CLEANUP::DONE" << std::endl;

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