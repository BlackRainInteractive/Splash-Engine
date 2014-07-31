//============================================================================
// Name        : FileIO.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include <string>

// The Splash Engine Namespace
namespace se{

	// The Utility Namespace
	namespace utility{

		// The FileIO Class
		class FileIO{
		public:

			// Functions
			static std::string LoadFromFile (std::string FilePath);
			static bool CopyFile (std::string TargetFile, std::string Destination);
			static bool MoveFile (std::string TargetFile, std::string Destination);
			static bool DeleteFile (std::string File);
		};
	}
}
