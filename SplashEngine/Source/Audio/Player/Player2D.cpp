//============================================================================
// Name        : Player2D.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "Player2D.h"
#include "../../Utility/DebugLog/DebugLog.h"
#include <FMOD/fmod.hpp>

// The Splash Engine Namespace
namespace se{

	// The Audio Namespace
	namespace audio{

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Load The Audio File
		bool Player2D::Load (std::string AudioPath, bool Loop){

			// Set The Default Audio Variables
			Player2D::loop   = Loop;
			Player2D::volume = 1;
			Player2D::pan	 = 0;
			Player2D::pitch	 = 1;

			// Set Sound Pointers To Null
			Player2D::soundStream  = nullptr;
			Player2D::soundChannel = nullptr;

			// Load The Sound
			FMOD_RESULT result = soundSystem -> createSound (AudioPath.c_str (), FMOD_2D, nullptr, &soundStream);

			// Check For Errors
			if (result != FMOD_OK){

				utility::DebugLog::WriteLog ("Could not load audio '" + AudioPath + "'", LOG_TYPE::WARNING);
				return false;
			}

			// Return Success
			return true;
		}
	}
}
