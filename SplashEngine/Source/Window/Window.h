#pragma once

#include <glm/glm.hpp>
#include <string>

// Forward Declare GLFW Window
struct GLFWwindow;

/*============================================================================================================*/

// The Splash Engine Namespace
namespace se{

	// The Window Class
	class Window{
	public:

		// Functions - Startup / Shutdown
		static bool Create (int Width, int Height, std::string Title, bool Fullscreen = false);

		// Functions - Window Settings
		static void SetSize		   (int Width, int Height);
		static void SetPosition	   (int X, int Y);
		static void SetTitle	   (std::string Title);
		static void SetClearColour (float Red, float Green, float Blue);
		static void ShowCursor	   (bool ShowCursor);

		// Functions - Rendering
		static bool Render ();

		// Variables - Window Settings
		static int width;
		static int height;
		static std::string title;

		// Variables - Matrices
		static glm::mat4 vpMatrix;

		// Variables - Window Handle
		static GLFWwindow* windowHandle;

	private:

		// Functions - GLEW Initialization
		static bool InitGLEW ();
	};
}