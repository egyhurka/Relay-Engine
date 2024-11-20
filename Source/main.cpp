/*
    KEY_ESCAPE = exit;
    KEY_F1 = wireframe mode;
    KEY_E = move up;
    KEY_Q = move down;
*/

#include "../Engine/_Core/Engine.cpp"

#include <iostream>

int main() {
    ENGINE::PRESET_SETUP(PRESET_DEFAULT);

    ENGINE::PRESET_SETUP(PRESET_B0);

    while (!ENGINE::WINDOW::RUNNING()) {
        // UPDATE
        ENGINE::UPDATE();

        // RENDERING
        ENGINE::RENDERER::DRAW();

        // UPDATE WINDOW
        ENGINE::WINDOW::UPDATE();
    }

    return EXIT_SUCCESS;
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

/* Cube and sphere distribution
ColorRGB color = { 0.0f, 1.0f, 0.0f };
    Mesh mesh(Mesh::createCubeVertices(), Mesh::createCubeIndices(), color, std::nullopt);
    auto mesh2 = mesh.clone();
    // IN PROGRESS: SHAPE (TRIANGLE AND MORE); COLOR METHOD (CONTINUOUS); SECOND COLOR ( std::nullopt); FADEFACTOR AND SCALE (1.0f, 1.0f)
    InstancedObjectDistributor cube(&mesh, &renderer, CUBE, CONTINUOUS, 5'000, 2222, ColorRGB(0.5f, 0.5f, 0.5f), std::nullopt, 1.0f, 1.0f, glm::vec2(-100.0f, 100.0f));
    InstancedObjectDistributor sphere(mesh2.get(), &renderer, SPHERE, CONTINUOUS, 2'000, 2223, ColorRGB(1.0f, 0.0f, 0.0f), std::nullopt, 1.0f, 1.0f, glm::vec2(-100.0f, 100.0f));

*/