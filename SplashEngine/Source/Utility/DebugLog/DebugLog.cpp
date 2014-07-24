//============================================================================
// Name        : DebugLog.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "DebugLog.h"
#include "../../Time/Time.h"
#include <iostream>

// The Splash Engine Namespace
namespace se{

	// The Utility Namespace
	namespace utility{

		// Declare Static Variables
		std::ofstream DebugLog::fileStream;

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Begin The Logging Operation
		bool DebugLog::BeginLog (){

			// Open Log File
			DebugLog::fileStream.open ("SplashEngine.log");

			// If Still Not Open, Return Error
			if (!DebugLog::fileStream.is_open ()){

				std::cout << "ERROR: Log file could not be created.\n";
				return false;
			}

			// Write Begin Log
			DebugLog::fileStream << "/*============================================================================================================*/\n";
			DebugLog::fileStream << "/*------BEGIN LOG---------------------------------------------------------------------------------------------*/\n";
			DebugLog::fileStream << "/*============================================================================================================*/\n\n";

			return true;
		}

/*============================================================================================================*/

		// Print To Log File
		void DebugLog::WriteLog (std::string Message, LOG_TYPE LogType){

			// The Time Variables
			int sec, min, hour;
			int day, month, year;

			// Get Time / Data Data
			Time::GetSystemTime (hour, min, sec);
			Time::GetSystemDate (day, month, year);

			// Write Time And Date
			DebugLog::fileStream << "[" << std::to_string (day) << "/" << std::to_string (month) << "/" << std::to_string (year) << "]";
			DebugLog::fileStream << " " << std::to_string (hour) << ":" << std::to_string (min) << ":" << std::to_string (sec) << " - ";

			// Switch Between Message Types
			switch (LogType){

			// Message
			case LOG_TYPE::MESSAGE:

				DebugLog::fileStream << Message << '\n';
				break;

			// Warning
			case LOG_TYPE::WARNING:

				DebugLog::fileStream << "WARNING: " << Message << '\n';
				break;

			// Error
			case LOG_TYPE::FATAL:

				DebugLog::fileStream << "ERROR: " << Message << '\n';
				DebugLog::EndLog ();
				exit (-1);
				break;
			}
		}

/*============================================================================================================*/

		// Destroy The Logger
		void DebugLog::EndLog (){

			// Write End Log
			DebugLog::fileStream << "\n/*============================================================================================================*/\n";
			DebugLog::fileStream << "/*------END LOG-----------------------------------------------------------------------------------------------*/\n";
			DebugLog::fileStream << "/*============================================================================================================*/\n\n";

			// Close File Stream
			DebugLog::fileStream.close ();
		}
	}
}
