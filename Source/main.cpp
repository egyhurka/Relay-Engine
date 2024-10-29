/*
    KEY_ESCAPE = exit;
    KEY_F1 = wireframe mode;
    KEY_E = move up;
    KEY_Q = move down;
*/

#include "../Engine/Window/Window.h"
#include "../Engine/Input/Input.h"
#include "../Engine/Renderer/Renderer.h"
#include "../Engine/Generation/InstancedObjectDistributor.h"

#include <iostream>
#include <random>

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const int width = 800, height = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
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

    camera.setNearPlane(0.01f);
    camera.setFarPlane(1000.0f);

    Renderer renderer(&camera);
    Input input(width, height, window.getWindow(), &camera);
    TimeManager time;

    time.init();
    double fpsLastTime = time.currentTime;
    renderer.init(&time);

    ColorRGB color = { 0.0f, 1.0f, 0.0f };
    Mesh mesh(Mesh::createCubeVertices(), Mesh::createCubeIndices(), color, std::nullopt);
    auto mesh2 = mesh.clone();
    // IN PROGRESS: SHAPE (TRIANGLE AND MORE); COLOR METHOD (CONTINUOUS); SECOND COLOR ( std::nullopt); FADEFACTOR AND SCALE (1.0f, 1.0f)
    InstancedObjectDistributor cube(&mesh, &renderer, CUBE, CONTINUOUS, 5'000, 2222, ColorRGB(0.5f, 0.5f, 0.5f), std::nullopt, 1.0f, 1.0f, glm::vec2(-100.0f, 100.0f));
    InstancedObjectDistributor sphere(mesh2.get(), &renderer, SPHERE, CONTINUOUS, 2'000, 2223, ColorRGB(1.0f, 0.0f, 0.0f), std::nullopt, 1.0f, 1.0f, glm::vec2(-100.0f, 100.0f));

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

/* 1 million cube rendering
    const int totalCubes = 1'000'000;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-300.0f, 300.0f);

    Mesh mesh(Mesh::createCubeVertices(), Mesh::createCubeIndices(), NULL, std::nullopt);
    InstancedObject instaceObject(&mesh);
    renderer.addMeshToRenderQueue(&mesh);

    Loader::batch(totalCubes, Loader::batchSizeCalculator(totalCubes), true, [&](int i) {
        glm::vec3 position(dis(gen), dis(gen), dis(gen));
        instaceObject.addInstancePosition(position);

        ColorRGB color(dis(gen), dis(gen), dis(gen));
        instaceObject.addInstanceColor(color);
    });

    instaceObject.setupInstances();
    renderer.addInstancedObjectToRenderQueue(&instaceObject);
*/