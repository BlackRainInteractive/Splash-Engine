#include "Engine.h"
#include "../Audio/Player/PlayerMusic.h"
#include "../Window/Window.h"
#include <FMOD/fmod.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

// The Splash Engine Namespace
namespace se{

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

	// Initialize The Engine
	bool Engine::Initialize (){

		// Print The Splash Engine Title
		std::cout << "-----------------------------------" << '\n';
		std::cout << "|   Splash Engine | Version 0.3   |" << '\n';
		std::cout << "| (C) 2014 Black Rain Interactive |" << '\n';
		std::cout << "-----------------------------------" << '\n';

		std::cout << "\nInitializing Libraries... ";

		// Init FMOD
		if (!Engine::InitFMOD ())
			return false;

		// Init GLFW
		if (!Engine::InitGLFW ())
			return false;

		// Print Success
		std::cout << "Done\n";

		return true;
	}

/*============================================================================================================*/

	// Shut Down The Engine
	void Engine::ShutDown (){

		// Shut Down FMOD
		audio::PlayerMusic::soundSystem -> close ();
		audio::PlayerMusic::soundSystem -> release ();

		// Shut Down GLFW
		glfwDestroyWindow (Window::windowHandle);
		glfwTerminate ();
	}

/*============================================================================================================*/
/*------PRIVATE FUNCTIONS-------------------------------------------------------------------------------------*/
/*============================================================================================================*/

	// Intialize FMOD
	bool Engine::InitFMOD (){

		// Create FMOD System
		audio::PlayerMusic::soundSystem = nullptr;
		FMOD_RESULT result = FMOD::System_Create (&audio::PlayerMusic::soundSystem);

		// Check For Errors
		if (result != FMOD_OK){

			std::cout << "Failed\n";
			std::cout << "ERROR: Could not initialize FMOD.\n";
			return false;
		}

		// Init FMOD
		result = audio::PlayerMusic::soundSystem -> init (512, FMOD_INIT_NORMAL, nullptr);

		// Check For Errors
		if (result != FMOD_OK){

			std::cout << "Failed\n";
			std::cout << "ERROR: Could not initialize FMOD.\n";
			return false;
		}

		// Return Success
		return true;
	}

/*============================================================================================================*/

	// Initialize GLFW
	bool Engine::InitGLFW (){

		// Init GLFW And Check For Errors
		if (!glfwInit ()){

			// Print Error
			std::cout << "Failed\n";
			std::cout << "ERROR: Could not initialize GLFW.\n";
			return false;
		}

		// Return True
		return true;
	}
}