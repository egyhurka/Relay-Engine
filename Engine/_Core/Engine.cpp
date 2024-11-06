#pragma once

#include "../Window/Window.h"
#include "../Renderer/Renderer.h"
#include "../Input/Input.h"

#include "../Generation/Random.h"
#include "../Generation/InstancedObjectDistributor.h"

namespace ENGINE {

// GENERAL ENGINE PRESETS
#define PRESET_DEFAULT	0x00
#define PRESET_A0		0x01

// SPECIAL PRESETS
#define PRESET_B0		0x10		// cube
#define PRESET_B1		0x11		// 10 cubes without intancing
#define PRESET_B2		0x12		// 100'000 cube with instancing

// LOOP PRESETS
#define PRESET_LOOP_1	0xA0

	namespace TIMEMANAGER {
		TimeManager time;
	}

	namespace CAMERA {
		Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
	}

	namespace WINDOW {
		unsigned int WIDTH = 800;
		unsigned int HEIGHT = 600;
		const char* TITLE = "ENGINE";
		Window window(WIDTH, HEIGHT, TITLE, &CAMERA::camera);

		void INITIALIZE() {
			window.noResize(true);
			window.captureMouse();

			glfwSetFramebufferSizeCallback(window.getWindow(), framebuffer_size_callback);
		}

		bool RUNNING() {
			return window.shouldClose();
		}

		void UPDATE() {
			window.swapBuffers();
			glfwPollEvents();
		}
	};

	namespace RENDERER {
		Renderer renderer(&CAMERA::camera);

		void INITIALIZE() {
			renderer.init(&TIMEMANAGER::time);
		}

		void UPDATE() {
			renderer.updateUniforms();
			Renderer::clearBuffers();
		}

		void DRAW() {
			Renderer::setBackgroundColor({ 0.0f, 0.0f, 0.0f, 1.0f });
			renderer.drawQueuedMeshes();
		}

		void VSYNC(bool interval) {
			Renderer::vSync(interval);
		}
	}

	namespace INPUT {
		Input input(WINDOW::WIDTH, WINDOW::HEIGHT, WINDOW::window.getWindow(), &CAMERA::camera);
	}

	// UPDATE LOOP
	void UPDATE() {
		// UPDATING TIME
		TIMEMANAGER::time.update();

		// PROCESSING INPUT
		INPUT::input.processInput(TIMEMANAGER::time.deltaTime);

		RENDERER::UPDATE();
	}

	std::vector<Mesh> meshStorage;
	void PRESET_SETUP(int PRESET) {
		switch (PRESET) {
		case PRESET_DEFAULT:
			WINDOW::WIDTH = 800;
			WINDOW::HEIGHT = 600;
			WINDOW::TITLE = "ENGINE";

			CAMERA::camera.setFarPlane(2000.0f);
			WINDOW::INITIALIZE();

			RENDERER::INITIALIZE();
			RENDERER::VSYNC(false);
			break;
		case PRESET_A0:
			WINDOW::WIDTH = 1920;
			WINDOW::HEIGHT = 1080;
			WINDOW::TITLE = "ENGINE";

			CAMERA::camera.setFarPlane(2000.0f);
			WINDOW::INITIALIZE();

			RENDERER::INITIALIZE();
			RENDERER::VSYNC(false);
			break;
		case PRESET_B0: {
			CAMERA::camera.position = glm::vec3(0.0f, 0.0f, 5.0f);
			ColorRGB color = { 0.0f, 0.5f, 1.0f };
			meshStorage.emplace_back(Mesh::createCubeVertices(), Mesh::createCubeIndices(), color);
			RENDERER::renderer.addMeshToRenderQueue(&meshStorage.back());
			break;
		}
		case PRESET_B1: {
			int count = 10;
			Random rnd(glm::vec2(-10, 10));

			for (int i = 0; i < count; i++) {
				Mesh mesh(Mesh::createCubeVertices(), Mesh::createCubeIndices(), rnd.randomColor());
				mesh.translate(rnd.randomPosition());
				meshStorage.push_back(mesh);
				RENDERER::renderer.addMeshToRenderQueue(&meshStorage.back());
			}

			/*Loader::simple(count, true, [&]() {
				meshStorage.emplace_back(Mesh::createCubeVertices(), Mesh::createCubeIndices(), rnd.randomColor());
				RENDERER::renderer.addMeshToRenderQueue(&meshStorage.back());
			});*/
			break;
		}
		case PRESET_LOOP_1: {
			ENGINE::UPDATE();
			RENDERER::DRAW();
			WINDOW::UPDATE();
			break;
		}
		default:
			break;
		}
	}
};