#include "Engine/Engine.h"
#include "Input/Input.h"
#include "Rendering/Camera/Camera.h"
#include "Rendering/Material/Material.h"
#include "Rendering/Primitive/Cube.h"
#include "Rendering/Primitive/Grid.h"
#include "Rendering/Primitive/Line.h"
#include "Rendering/SceneManager/SceneManager.h"
#include "Rendering/Skybox/Skybox.h"
#include "Rendering/Texture/Texture.h"
#include "Time/Time.h"
#include "Utility/Display/Display.h"
#include "Window/Window.h"

void EngineTest (){

	// Create Scene Manager
	se::rendering::SceneManager sManager;

	// Setup Camera
	se::rendering::Camera camera;
	camera.SetupCamera (se::CAMERA_TYPE::PERSPECTIVE, se::CAMERA_MODE::FPS);
	camera.SetupPerspective (60);
	camera.SetupFPS (0.9f, 10);
	camera.Transform (glm::vec3 (0, 1, -4), glm::vec3 (0));

	// Load Skybox Shader
	se::rendering::Material matSkybox;
	matSkybox.Load (se::DEFAULT_MATERIAL::SKYBOX);

	// Load Post Pass Shader
	se::rendering::Material matPostPass;
	matPostPass.Load (se::DEFAULT_MATERIAL::POSTPASS);

	// Load Line Shader
	se::rendering::Material matLine;
	matLine.Load (se::DEFAULT_MATERIAL::PRIMITIVE);

	// Load Skybox
	//se::rendering::Skybox skybox;
	//skybox.Load ("TestResources/left.tif", "TestResources/right.tif", "TestResources/down.tif", "TestResources/up.tif", "TestResources/front.tif", "TestResources/back.tif", &matSkybox);
	//sManager.Add (&skybox);

	// Create Line X Axis
	se::rendering::Line lineX;
	lineX.Create (glm::vec3 (0), glm::vec3 (2, 0, 0), glm::vec3 (1, 0, 0), &matLine);
	sManager.Add (&lineX);

	// Create Line Y Axis
	se::rendering::Line lineY;
	lineY.Create (glm::vec3 (0), glm::vec3 (0, 2, 0), glm::vec3 (0, 1, 0), &matLine);
	sManager.Add (&lineY);

	// Create Line Z Axis
	se::rendering::Line lineZ;
	lineZ.Create (glm::vec3 (0), glm::vec3 (0, 0, 2), glm::vec3 (0, 0, 1), &matLine);
	sManager.Add (&lineZ);

	// Create A Grid
	se::rendering::Grid grid;
	grid.Create (glm::vec3 (0, -0.001f, 0), 20, glm::vec3 (0), &matLine);
	sManager.Add (&grid);

	// Create A Cube
	se::rendering::Cube cube;
	cube.Create (glm::vec3 (5, 0.5f, 5), glm::vec3 (1, 1, 4), glm::vec3 (1, 0, 0), &matLine);
	cube.SetParent (&grid);
	sManager.Add (&cube);

	// The Main Render Loop
	while (se::Window::Render () && !se::Input::GetKeyPressed (se::KEY::KEY_ESCAPE)){

		// Update The Camera
		camera.Update ();

		// Rotate The Cube
		cube.Transform (cube.position, glm::vec3 (0, (float) se::Time::GetElapsedTime () * 100, 0));

		// Rotate The Grid
		if (se::Input::GetKeyPressed (se::KEY::KEY_ENTER))
			grid.Transform (grid.position, glm::vec3 (0, grid.rotation.y - (float) se::Time::deltaTime * 50, 0));

		// Render The Scene
		sManager.DrawAll (&camera, &matPostPass);
	}
}

int main (){

	// Init Engine
	se::Engine::Initialize ();

	// Create Window And Hide Cursor
	se::Window::Create (1280, 720, "Splash Engine | Revision 3");
	se::Window::ShowCursor (false);

	// Center Cursor
	se::Input::SetMousePos (se::Window::width / 2, se::Window::height / 2);

	// Run Engine Test
	EngineTest ();

	// Shutdown The Engine
	se::Engine::ShutDown ();

	return 0;
}
