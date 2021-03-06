//============================================================================
// Name        : Time.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

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
		static void GetSystemTime (int &Hours, int &Minutes, int &Seconds);
		static void GetSystemDate (int &Day, int &Month, int &Year);

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
