#include "Engine/Engine.h"
#include "Input/Input.h"
#include "Rendering/Camera/Camera.h"
#include "Rendering/Material/Material.h"
#include "Rendering/Primitive/Line.h"
#include "Rendering/SceneManager/SceneManager.h"
#include "Rendering/Skybox/Skybox.h"
#include "Rendering/Texture/Texture.h"
#include "Time/Time.h"
#include "Utility/Display/Display.h"
#include "Window/Window.h"
#include <iostream>

void EngineTest (){

	// Create Scene Manager
	se::rendering::SceneManager sManager;

	// Center Cursor
	se::Input::SetMousePos (se::Window::width / 2, se::Window::height / 2);

	// Setup Camera
	se::rendering::Camera camera;
	camera.SetupCamera (se::CAMERA_TYPE::PERSPECTIVE, se::CAMERA_MODE::FPS);
	camera.SetupPerspective (60);
	camera.SetupFPS (0.3f, 10);
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
	se::rendering::Skybox skybox;
	skybox.Load ("TestResources/left.tif", "TestResources/right.tif", "TestResources/down.tif", "TestResources/up.tif", "TestResources/front.tif", "TestResources/back.tif", &matSkybox);
	sManager.Add (&skybox);

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

	// The Main Render Loop
	while (se::Window::Render () && !se::Input::GetKeyPressed (se::KEY::KEY_ESCAPE)){

		// Update The Camera
		camera.Update ();

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

	// Run Engine Test
	EngineTest ();

	// Shutdown The Engine
	se::Engine::ShutDown ();

	return 0;
}
