#include "seBase.h"
#include "seInput.h"
#include "seRendering.h"
#include "seTime.h"

void EngineTest (){

	// Create Scene Manager
	se::rendering::SceneManager sManager;

	// Setup Camera
	se::rendering::CameraFly camera;
	camera.SetupCamera (se::CAMERA_MODE::PERSPECTIVE, 5, 50);
	camera.SetProjection (60);
	camera.Transform (glm::vec3 (0, 1, -4.25f), glm::vec3 (0));
	sManager.Add (&camera);

	// Load Post Pass Shader
	se::rendering::Material matPostPass;
	matPostPass.Load (se::DEFAULT_MATERIAL::POSTPASS);

	// Load Solid Shader
	se::rendering::Material matSolid;
	matSolid.Load (se::DEFAULT_MATERIAL::PRIMITIVE_SOLID);

	// Load Line Shader
	se::rendering::Material matLine;
	matLine.Load (se::DEFAULT_MATERIAL::PRIMITIVE_LINE);

	// Load Mesh Shader
	se::rendering::Material matMesh;
	matMesh.Load ("Shaders/Mesh/Mesh.vert", "", "", "", "Shaders/Mesh/Mesh.frag");

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

	// Create First Cube
	se::rendering::Cube cube;
	cube.Create (glm::vec3 (5, 0.5f, 5), glm::vec3 (1, 1, 5), glm::vec3 (1, 0, 0), &matSolid);
	cube.SetParent (&grid);
	sManager.Add (&cube);

	// Create Second Cube
	se::rendering::Cube cube2;
	cube2.Create (glm::vec3 (0, 1, 2), glm::vec3 (1, 1, 5), glm::vec3 (0, 1, 0), &matSolid);
	cube2.SetParent (&cube);
	sManager.Add (&cube2);

	// Create Third Cube
	se::rendering::Cube cube3;
	cube3.Create (glm::vec3 (0, 1, 2), glm::vec3 (1, 1, 4), glm::vec3 (0, 0, 1), &matSolid);
	cube3.SetParent (&cube2);
	sManager.Add (&cube3);

	// Create A Sphere
	se::rendering::Sphere sphere;
	sphere.Create (glm::vec3 (-5, 1, 0), 1, 32, 16, glm::vec3 (1), &matSolid);
	sphere.SetParent (&grid);
	sManager.Add (&sphere);

	// The Main Render Loop
	while (se::Window::Render () && !se::Input::GetKeyPressed (se::KEY::KEY_ESCAPE)){

		// Update The Camera
		camera.Update ();

		// Rotate The Cubes
		cube.Transform  (cube.position,  glm::vec3 (0, (float) se::Time::GetElapsedTime () * 100, 0));
		cube2.Transform (cube2.position, glm::vec3 (0, (float) -se::Time::GetElapsedTime () * 200, 0));
		cube3.Transform (cube2.position, glm::vec3 (0, (float) se::Time::GetElapsedTime () * 100, 0));

		// Rotate The Grid
		if (se::Input::GetKeyPressed (se::KEY::KEY_ENTER)){

			grid.Transform (grid.position, glm::vec3 (grid.rotation.x - (float) se::Time::deltaTime * 25, 
													  grid.rotation.y - (float) se::Time::deltaTime * 50, 
													  grid.rotation.z + (float) se::Time::deltaTime * 75));
		}

		// Render The Scene
		sManager.DrawAll (&matPostPass);
	}
}

int main (){

	// Init Engine
	se::Engine::Initialize ();

	// Create Window And Hide Cursor
	se::Window::Create (1280, 720, "Splash Engine | Revision 3", false);
	se::Window::ShowCursor (false);

	// Center Cursor
	se::Input::SetMousePos (se::Window::width / 2, se::Window::height / 2);

	// Run Engine Test
	EngineTest ();

	// Shutdown The Engine
	se::Engine::ShutDown ();

	return 0;
}
