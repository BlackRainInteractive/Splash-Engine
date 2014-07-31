//============================================================================
// Name        : Window.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "Window.h"
#include "../Audio/Player/PlayerMusic.h"
#include "../Input/Input.h"
#include "../Time/Time.h"
#include "../Utility/DebugLog/DebugLog.h"
#include <FMOD/fmod.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// The Splash Engine Namespace
namespace se{

	// Define Static Variables
	int Window::width;
	int Window::height;
	std::string Window::title;
	glm::mat4 Window::vpMatrix;
	GLFWwindow* Window::windowHandle;

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

	// Create The Window
	bool Window::Create (int Width, int Height, std::string Title, bool Fullscreen){

		// Set The Window Variables
		Window::width  = Width;
		Window::height = Height;
		Window::title  = Title;

		// Create The VP Matrix
		Window::vpMatrix = glm::mat4 (glm::vec4 (Width / 2, 0.0f, 0.0f, 0.0f),
									  glm::vec4 (0.0f, Height / 2, 0.0f, 0.0f),
									  glm::vec4 (0.0f, 0.0f, 1.0f, 0.0f),
									  glm::vec4 (Width / 2, Height / 2, 0.0f, 1.0f));

		// Print Creating Window
		utility::DebugLog::WriteLog ("Creating window", LOG_TYPE::MESSAGE);

		// Create The Window
		if (Fullscreen)
			Window::windowHandle = glfwCreateWindow (Width, Height, Title.c_str (), glfwGetPrimaryMonitor (), nullptr);

		else
			Window::windowHandle = glfwCreateWindow (Width, Height, Title.c_str (), nullptr, nullptr);

		// Check If Creation Failed
		if (!Window::windowHandle){

			utility::DebugLog::WriteLog ("Window creation failed", LOG_TYPE::FATAL);
			return false;
		}

		// Create The OpenGL Context
		if (!Window::InitGLEW ())
			return false;

		// Enable Required OpenGL Functionality
		glEnable (GL_DEPTH_TEST);
		glEnable (GL_CULL_FACE);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Set The Window Clear Colour
		glClearColor (0.24f, 0.24f, 0.24f, 1);

		// Print OpenGL Version
		std::cout << "\nUsing OpenGL Version " << glGetString (GL_VERSION) << '\n';
		std::cout << "OpenGL Vendor - " << glGetString (GL_VENDOR) << "\n\n";

		return true;
	}

/*============================================================================================================*/

	// Set The Window Hint
	void Window::SetWindowHint (WINDOW_HINT WindowHint, bool Value){
		glfwWindowHint (WindowHint, Value);
	}

/*============================================================================================================*/

	// Set The Window Size
	void Window::SetSize (int Width, int Height){

		// Set Variables
		Window::width  = Width;
		Window::height = Height;

		// Set The VP Matrix
		Window::vpMatrix = glm::mat4 (glm::vec4 (Width / 2, 0.0f, 0.0f, 0.0f),
									  glm::vec4 (0.0f, Height / 2, 0.0f, 0.0f),
									  glm::vec4 (0.0f, 0.0f, 1.0f, 0.0f),
									  glm::vec4 (Width / 2, Height / 2, 0.0f, 1.0f));

		// Set The Window Size
		glfwSetWindowSize (Window::windowHandle, Width, Height);
	}

/*============================================================================================================*/

	// Set The Window Position
	void Window::SetPosition (int X, int Y){
		glfwSetWindowPos (Window::windowHandle, X, Y);
	}

/*============================================================================================================*/

	// Set The Window Title
	void Window::SetTitle (std::string Title){

		Window::title = Title;
		glfwSetWindowTitle (Window::windowHandle, Title.c_str ());
	}

/*============================================================================================================*/

	// Set The Window Clear Colour
	void Window::SetClearColour (float Red, float Green, float Blue){
		glClearColor (Red, Green, Blue, 1);
	}

/*============================================================================================================*/

	// Toggle The Window Cursor
	void Window::ShowCursor (bool ShowCursor){

		// Check If True (Show Cursor)
		if (ShowCursor)
			glfwSetInputMode (Window::windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		// Otherwise, Hide Cursor
		else
			glfwSetInputMode (Window::windowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

/*============================================================================================================*/

	// Render The Window
	bool Window::Render (){

		// Check If Window Should Close
		if (glfwWindowShouldClose (Window::windowHandle))
			return false;

		// Calc Delta Time And FPS
		Time::CalcDeltaTime ();
		Time::CalcFPS ();

		// Poll Events
		glfwPollEvents ();

		// Swap The Buffers And Clear The Window
		glfwSwapBuffers (Window::windowHandle);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Update Sound System
		audio::PlayerMusic::soundSystem -> update ();

		return true;
	}

/*============================================================================================================*/
/*------PRIVATE FUNCTIONS-------------------------------------------------------------------------------------*/
/*============================================================================================================*/

	// Initialize GLEW
	bool Window::InitGLEW (){

		// Print Creating Context
		utility::DebugLog::WriteLog ("Creating OpenGL context", LOG_TYPE::MESSAGE);

		// Create The OpenGL Context
		glfwMakeContextCurrent (Window::windowHandle);

		// Init Glew And Check For Errors
		glewExperimental = true;
		GLenum err = glewInit ();

		if (err != GLEW_OK){

			utility::DebugLog::WriteLog ("Context could not be created. " + std::string ((char*) glewGetErrorString (err)), LOG_TYPE::FATAL);
			return false;
		}

		return true;
	}
}
