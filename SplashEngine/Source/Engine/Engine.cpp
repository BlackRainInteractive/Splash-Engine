//============================================================================
// Name        : Engine.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "Engine.h"
#include "../Audio/Player/PlayerMusic.h"
#include "../Utility/DebugLog/DebugLog.h"
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

		// Start The Debug Log
		utility::DebugLog::BeginLog ();

		// Print The Splash Engine Title
		std::cout << "-----------------------------------\n";
		std::cout << "|   Splash Engine | Version 0.3   |\n";
		std::cout << "| (C) 2014 Black Rain Interactive |\n";
		std::cout << "-----------------------------------\n";

		utility::DebugLog::WriteLog ("Beginning library initialization", LOG_TYPE::MESSAGE);

		// Init FMOD
		utility::DebugLog::WriteLog ("Starting FMOD", LOG_TYPE::MESSAGE);

		if (!Engine::InitFMOD ())
			return false;

		// Init GLFW
		utility::DebugLog::WriteLog ("Starting GLFW", LOG_TYPE::MESSAGE);

		if (!Engine::InitGLFW ())
			return false;

		return true;
	}

/*============================================================================================================*/

	// Shut Down The Engine
	void Engine::ShutDown (){

		utility::DebugLog::WriteLog ("Shutting down engine", LOG_TYPE::MESSAGE);

		// Shut Down FMOD
		audio::PlayerMusic::soundSystem -> close ();
		audio::PlayerMusic::soundSystem -> release ();

		// Shut Down GLFW
		glfwDestroyWindow (Window::windowHandle);
		glfwTerminate ();

		// End Debug Log
		utility::DebugLog::EndLog ();
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

			utility::DebugLog::WriteLog ("Could not initialize FMOD", LOG_TYPE::FATAL);
			return false;
		}

		// Init FMOD
		result = audio::PlayerMusic::soundSystem -> init (512, FMOD_INIT_NORMAL, nullptr);

		// Check For Errors
		if (result != FMOD_OK){

			utility::DebugLog::WriteLog ("Could not initialize FMOD", LOG_TYPE::FATAL);
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
			utility::DebugLog::WriteLog ("Could not initialize GLFW", LOG_TYPE::FATAL);
			return false;
		}

		// Return True
		return true;
	}
}
