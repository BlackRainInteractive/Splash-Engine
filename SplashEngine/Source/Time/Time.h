#pragma once

// The Splash Engine Namespace
namespace se{

	// The Time Class
	class Time{
	public:

		// Functions
		static void CalcDeltaTime ();
		static void CalcFPS ();
		static void Wait (double WaitTime);
		static double GetElapsedTime ();

		// Variables
		static double deltaTime;
		static int fps;

	private:

		// Variables
		static double previousFrame;
		static double currentFrame;
		static double timePerFrame;
		static int frameCount;
	};
}