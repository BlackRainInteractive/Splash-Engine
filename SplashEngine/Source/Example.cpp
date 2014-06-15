#include "Engine/Engine.h"
#include "Input/Input.h"
#include "Rendering/Camera/Camera.h"
#include "Rendering/Material/Material.h"
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

	// Load Skybox Shader
	se::rendering::Material matSkybox;
	matSkybox.Load ("Shaders/Skybox/Skybox.vert", "", "", "", "Shaders/Skybox/Skybox.frag");

	// Load Post Pass Shader
	se::rendering::Material matPostPass;
	matPostPass.Load ("Shaders/PostPass/PostPass.vert", "", "", "", "Shaders/PostPass/PostPass.frag");

	// Load Skybox
	se::rendering::Skybox skybox;
	skybox.Load ("TestResources/left.tif", "TestResources/right.tif", "TestResources/down.tif", "TestResources/up.tif", "TestResources/front.tif", "TestResources/back.tif", &matSkybox);
	sManager.Add (&skybox);

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
