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
		static bool InitGLFW ();
	};
}