//============================================================================
// Name        : Time.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "Time.h"
#include <GLFW/glfw3.h>
#include <ctime>

// The Splash Engine Namespace
namespace se{

	// Define Static Variables - Public
	double Time::deltaTime;
	int Time::fps;

	// Define Static Variables - Private
	double Time::previousFrame;
	double Time::currentFrame;
	double Time::timePerFrame;
	int Time::frameCount;

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

	// Calculate Delta Time
	void Time::CalcDeltaTime (){

		Time::currentFrame = glfwGetTime ();
		Time::deltaTime = (Time::currentFrame - Time::previousFrame);
		Time::previousFrame = Time::currentFrame;
	}

/*============================================================================================================*/

	// Calculate Frame Rate
	void Time::CalcFPS (){

		// Check If 1 Second Has Passed. If Not, Add To Frame Count
		if (Time::timePerFrame < 1){

			Time::frameCount += 1;
			Time::timePerFrame += Time::deltaTime;
		}

		// Otherwise, Reset Frame Count
		else{

			// Reset Variables
			Time::fps = Time::frameCount;
			Time::frameCount = 0;
			Time::timePerFrame = 0.0;
		}
	}

/*============================================================================================================*/

	// Wait For Number Of Seconds
	void Time::Wait (double WaitTime){

		// Create Variables
		double timer = 0.0;

		// Wait Loop
		while (timer < WaitTime){

			// Calc Delta Time And Add To Timer
			Time::CalcDeltaTime();
			timer += Time::deltaTime;
		}
	}

/*============================================================================================================*/

	// Get The Elapsed Time
	double Time::GetElapsedTime(){
		return glfwGetTime ();
	}

/*============================================================================================================*/

	// Get The Current System Time
	void Time::GetSystemTime (int &Hours, int &Minutes, int &Seconds){

		// Get Time
		time_t t = time (0);

		// Create Time Struct
		tm* sysTime = localtime (&t);

		// Return Time Values
		Hours   = sysTime -> tm_hour;
		Minutes = sysTime -> tm_min;
		Seconds = sysTime -> tm_sec;
	}

/*============================================================================================================*/

	// Get The Current System Date
	void Time::GetSystemDate (int &Day, int &Month, int &Year){

		// Get Time
		time_t t = time (0);

		// Create Time Struct
		tm* sysTime = localtime (&t);

		// Return Date Values
		Day   = sysTime -> tm_mday;
		Month = sysTime -> tm_mon + 1;
		Year  = sysTime -> tm_year + 1900;
	}
}
