#pragma once

#include <string>

// The Splash Engine Namespace
namespace se{

	// The Utility Namespace
	namespace utility{

		// The INI Parser Class
		class IniParser{
		public:

			// Functions - File Loading
			bool LoadFile (std::string File);
			bool Reload	();

			// Functions - Data Returning
			std::string GetString (std::string Section, std::string Key);
			int GetInt			  (std::string Section, std::string Key);
			float GetFloat		  (std::string Section, std::string Key);
			double GetDouble	  (std::string Section, std::string Key);
			bool GetBool		  (std::string Section, std::string Key);

			// Variables
			std::string iniContents;
			std::string filePath;
		};
	}
}