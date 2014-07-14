//============================================================================
// Name        : Engine.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

// The Splash Engine Namespace
namespace se{

	// The Engine Class
	class Engine{
	public:

		// Functions - Startup / Shutdown
		static bool Initialize ();
		static void ShutDown ();

	private:

		// Functions - Library Initialization
		static bool InitFMOD ();
		static bool InitGLFW ();
	};
}
