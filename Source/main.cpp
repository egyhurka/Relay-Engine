/*
    KEY_ESCAPE = exit;
    KEY_F1 = wireframe mode;
*/

#include "../Engine/Window/Window.h"
#include "../Engine/Input/Input.h"
#include "../Engine/Renderer/Renderer.h"

#include <iostream>

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const int width = 800, height = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = width / 2.0f;
float lastY = height / 2.0f;
bool firstMouse = true;

double lastTime = glfwGetTime();
int nbFrames = 0;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
    Window window(width, height, "Relay Engine");
    window.noResize(true);
    window.create();
    window.captureMouse();
    glfwSetFramebufferSizeCallback(window.getWindow(), framebuffer_size_callback);
    glfwSetCursorPosCallback(window.getWindow(), mouse_callback);

    Renderer renderer(&camera);
    Input input(width, height, window.getWindow(), &camera);

    renderer.init();

    std::vector<GLfloat> vertices = {
        -0.5f, -0.5f, -0.5f, // 0
         0.5f, -0.5f, -0.5f, // 1
         0.5f,  0.5f, -0.5f, // 2
         -0.5f,  0.5f, -0.5f, // 3
         -0.5f, -0.5f,  0.5f, // 4
         0.5f, -0.5f,  0.5f, // 5
         0.5f,  0.5f,  0.5f, // 6
         -0.5f,  0.5f,  0.5f  // 7
    };

    std::vector<GLuint> indices = {
        0, 1, 2, 0, 2, 3, // back
        4, 5, 6, 4, 6, 7, // front
        0, 1, 5, 0, 5, 4, // left
        2, 3, 7, 2, 7, 6, // right
        3, 0, 4, 3, 4, 7, // top
        1, 2, 6, 1, 6, 5  // bottom
    };

    ColorRGB color(0.0f, 1.0f, 0.5f);

    // not working yet
    std::optional<Texture> texture = std::nullopt; //std::make_optional<Texture>("Source/Textures/tex0.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE)
    Mesh mesh(vertices, indices, {0.0f, 1.0f, 0.0f}, texture);
    Mesh mesh2(vertices, indices, { 1.0f, 1.0f, 0.0f }, texture);
    mesh2.translate(glm::vec3(2.0f, 1.0f, 0.0f));

    renderer.addMeshToRenderQueue(&mesh);
    renderer.addMeshToRenderQueue(&mesh2);

    Renderer::vSync(false);

    while (!window.shouldClose()) {
        double currentTime = glfwGetTime();
        nbFrames++;

        // FPS
        if (currentTime - lastTime >= 1.0) {
            double fps = static_cast<double>(nbFrames) / (currentTime - lastTime);
            std::string newTitle = "Relay Engine | FPS: " + std::to_string(static_cast<int>(fps));
            window.setTitle(newTitle.c_str());

            nbFrames = 0;
            lastTime = currentTime;
        }

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // INPUT PROCESSING
        input.processInput(deltaTime);

        // RENDERING
        Renderer::clearBuffers();
        renderer.drawQueuedMeshes();

        window.swapBuffers();
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}