//============================================================================
// Name        : DebugLog.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include <fstream>
#include <string>

// The Splash Engine Namespace
namespace se{

	// The Log Type Enum
	enum LOG_TYPE{

		MESSAGE = 0,
		WARNING = 1,
		ERROR   = 2
	};

//============================================================================

	// The Utility Namespace
	namespace utility{

		// The Debug Log Class
		class DebugLog{
		public:

			// Functions
			static bool BeginLog ();
			static void WriteLog (std::string Message, LOG_TYPE LogType);
			static void EndLog ();

		private:

			// Variables
			static std::ofstream fileStream;
		};
	}
}
