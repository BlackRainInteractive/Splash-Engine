//============================================================================
// Name        : IniParser.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "IniParser.h"
#include "../DebugLog/DebugLog.h"
#include "../FileIO/FileIO.h"
#include <algorithm>

// The Splash Engine Namespace
namespace se{

	// The Utility Namespace
	namespace utility{

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Load The Ini File
		bool IniParser::LoadFile (std::string File){

			// Set Parser Variables
			IniParser::filePath = File;
			IniParser::iniContents = FileIO::LoadFromFile (File);

			// Check For Errors
			if (IniParser::iniContents == ""){

				DebugLog::WriteLog ("Could not load INI file '" + File + "'", LOG_TYPE::WARNING);
				return false;
			}

			// Return Success
			return true;
		}

/*============================================================================================================*/

		// Reload The Ini File
		bool IniParser::Reload (){

			IniParser::iniContents.clear ();
			return (IniParser::LoadFile (IniParser::filePath));
		}

/*============================================================================================================*/

		// Get A String From The Ini File
		std::string IniParser::GetString (std::string Section, std::string Key){

			// Create And Init Variables
			std::string sectionString = "[" + std::string (Section) + "]";
			int startPos = IniParser::iniContents.find (sectionString), endPos = 0;

			// Check If Section Exists
			if (startPos != std::string::npos){

				// Get The End Position
				endPos = IniParser::iniContents.find ('[', startPos + 1);

				// Cut Out Section
				std::string firstPass = IniParser::iniContents.substr (startPos, endPos - startPos);

				// Check If Key Exists
				startPos = firstPass.find (std::string (Key));

				// Do If Key Is Found
				if (startPos != std::string::npos){

					// Get The End Position
					endPos = firstPass.find ("\n", startPos + 1);

					// Extract The Line
					std::string returnString = firstPass.substr (startPos, endPos - startPos);
					std::string removeKey = std::string (Key) + "=";

					// Remove Spaces And Key
					returnString.erase (std::remove_if (returnString.begin (), returnString.end (), isspace), returnString.end ());
					returnString.erase (0, removeKey.length ());

					// Return The Result
					return (returnString);
				}
			}

			// Return Faliure
			return ("");
		}

/*============================================================================================================*/

		// Get An Int From The File
		int IniParser::GetInt (std::string Section, std::string Key){
			return (std::stoi (IniParser::GetString (Section, Key)));
		}

/*============================================================================================================*/

		// Get A Float From The File
		float IniParser::GetFloat (std::string Section, std::string Key){
			return (std::stof (IniParser::GetString (Section, Key)));
		}

/*============================================================================================================*/

		// Get A Double From The File
		double IniParser::GetDouble (std::string Section, std::string Key){
			return (std::stod (IniParser::GetString (Section, Key)));
		}

/*============================================================================================================*/

		// Get A Bool From The File
		bool IniParser::GetBool (std::string Section, std::string Key){

			// Get String
			std::string bValue = IniParser::GetString (Section, Key);

			// Check If True
			if (bValue == "1" || bValue == "true" || bValue == "True" || bValue == "TRUE")
				return true;

			// Check If False
			else if (bValue == "0" || bValue == "false" || bValue == "False" || bValue == "FALSE")
				return false;

			// Return False
			else
				return false;
		}
	}
}
