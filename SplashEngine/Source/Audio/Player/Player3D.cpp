//============================================================================
// Name        : Player3D.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "Player3D.h"
#include "../../Rendering/Camera/Camera.h"
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
		bool Player3D::Load (std::string AudioPath, bool Loop){

			// Set The Default Audio Variables
			Player3D::loop   = Loop;
			Player3D::volume = 1;
			Player3D::pan	 = 0;
			Player3D::pitch	 = 1;

			// Set Sound Pointers To Null
			Player3D::soundStream  = nullptr;
			Player3D::soundChannel = nullptr;

			// Load The Sound
			FMOD_RESULT result = soundSystem -> createSound (AudioPath.c_str (), FMOD_3D, nullptr, &soundStream);

			// Check For Errors
			if (result != FMOD_OK){

				utility::DebugLog::WriteLog ("Could not load audio '" + AudioPath + "'", LOG_TYPE::WARNING);
				return false;
			}

			// Return Success
			return true;
		}

//============================================================================

		// Update The Sound
		void Player3D::Update (rendering::Camera* Camera){

			// Set Sound Position
			FMOD_VECTOR soundPos = {Player3D::position.x, Player3D::position.y, Player3D::position.z};
			Player3D::soundChannel -> set3DAttributes (&soundPos, 0, 0);

			// Set Sound Listener Position
			FMOD_VECTOR forward		= {Camera -> vMatrix [2].x, Camera -> vMatrix [2].y, Camera -> vMatrix [2].z};
			FMOD_VECTOR up			= {0, 1, 0};
			FMOD_VECTOR translation = {Camera -> vMatrix [3].x, Camera -> vMatrix [3].y, Camera -> vMatrix [3].z};

			PlayerMusic::soundSystem -> set3DListenerAttributes (0, &translation, 0, &forward, &up);
		}
	}
}