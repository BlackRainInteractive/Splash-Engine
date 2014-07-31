//============================================================================
// Name        : FileIO.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "FileIO.h"
#include "../DebugLog/DebugLog.h"

// The Splash Engine Namespace
namespace se{

	// The Utility Namespace
	namespace utility{

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Load A File To A String
		std::string FileIO::LoadFromFile (std::string FilePath){

			// Load The File
			std::ifstream fileStream (FilePath);

			// Check If File Was Loaded
			if (fileStream.is_open ()){

				// Create The String
				std::string returnString ((std::istreambuf_iterator <char> (fileStream)),
										   std::istreambuf_iterator <char> ());

				// Close The File Stream
				fileStream.close ();

				// Return
				return (returnString);
			}

			// Return Error
			else
				return (std::string (""));
		}

/*============================================================================================================*/

		// Copy A File
		bool FileIO::CopyFile (std::string TargetFile, std::string Destination){

			// Open Source File
			std::ifstream source (TargetFile, std::ios::binary);

			// Check If Found
			if (!source.is_open ()){

				DebugLog::WriteLog ("Failed to copy file '" + TargetFile + "'. File not found", LOG_TYPE::WARNING);
				return false;
			}

			// Create Destination File
			std::ofstream destination (Destination, std::ios::binary);

			// Check For Errors
			if (!destination.is_open ()){

				DebugLog::WriteLog ("Failed to copy file '" + TargetFile + "'. Destination may be write protected", LOG_TYPE::WARNING);
				return false;
			}

			// Copy Data
			destination << source.rdbuf ();

			// Close Streams
			source.close ();
			destination.close ();

			return true;
		}

/*============================================================================================================*/

		// Move A File
		bool FileIO::MoveFile (std::string TargetFile, std::string Destination){

			// Copy The File And Remove Original
			if (FileIO::CopyFile (TargetFile, Destination)){

				FileIO::DeleteFile (TargetFile);
				return true;
			}

			else
				return false;
		}

/*============================================================================================================*/

		// Delete A File
		bool FileIO::DeleteFile (std::string File){

			// Try To Delete File And Check For Errors
			if (std::remove (File.c_str ()) != 0){

				DebugLog::WriteLog ("Failed to delete file '" + File + "'. File may be in use.", LOG_TYPE::WARNING);
				return false;
			}

			else
				return true;
		}
	}
}
