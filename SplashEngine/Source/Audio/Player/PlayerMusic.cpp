//============================================================================
// Name        : PlayerMusic.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "PlayerMusic.h"
#include "../../Utility/DebugLog/DebugLog.h"
#include <FMOD/fmod.hpp>

// The Splash Engine Namespace
namespace se{

	// The Audio Namespace
	namespace audio{

		// Define Static Variables
		FMOD::System* PlayerMusic::soundSystem;

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Load The Audio File
		bool PlayerMusic::Load (std::string AudioPath, bool Loop){

			// Set The Default Audio Variables
			PlayerMusic::loop   = Loop;
			PlayerMusic::volume = 1;
			PlayerMusic::pan	= 0;
			PlayerMusic::pitch	= 1;

			// Set Sound Pointers To Null
			PlayerMusic::soundStream  = nullptr;
			PlayerMusic::soundChannel = nullptr;

			// Load The Sound
			FMOD_RESULT result = soundSystem -> createStream (AudioPath.c_str (), FMOD_2D, nullptr, &soundStream);

			// Check For Errors
			if (result != FMOD_OK){

				utility::DebugLog::WriteLog ("Could not load audio '" + AudioPath + "'", LOG_TYPE::WARNING);
				return false;
			}

			// Return Success
			return true;
		}

/*============================================================================================================*/

		// Play The Audio
		bool PlayerMusic::Play (){

			// Check If Audio Is Currently Playing
			if (PlayerMusic::soundChannel -> isPlaying (false)){

				// Play The Sound
				FMOD_RESULT result = soundSystem -> playSound (soundStream, nullptr, false, &soundChannel);

				// Check For Errors
				if (result != FMOD_OK){

					utility::DebugLog::WriteLog ("Failed to play audio", LOG_TYPE::WARNING);
					return false;
				}

				// Set Looping
				if (PlayerMusic::loop)
					PlayerMusic::soundChannel -> setMode (FMOD_LOOP_NORMAL);

				// Set Volume, Pitch, And Pan
				PlayerMusic::soundChannel -> setVolume (PlayerMusic::volume);
				PlayerMusic::soundChannel -> setPan (PlayerMusic::pan);
				PlayerMusic::soundChannel -> setPitch (PlayerMusic::pitch);
			}

			// Check If Sound Is Paused
			else if (PlayerMusic::soundChannel -> getPaused (false))
				PlayerMusic::soundChannel -> setPaused (false);

			// Return Success
			return true;
		}

/*============================================================================================================*/

		// Pause The Audio
		void PlayerMusic::Pause (){

			// Check If Audio Is Playing
			if (!PlayerMusic::soundChannel -> isPlaying (false) && PlayerMusic::soundChannel -> getPaused (false))
				PlayerMusic::soundChannel -> setPaused (true);
		}

/*============================================================================================================*/

		// Stop The Audio
		void PlayerMusic::Stop (){
			PlayerMusic::soundChannel -> stop ();
		}

/*============================================================================================================*/

		// Set The Volume
		void PlayerMusic::SetVolume (float Volume){

			PlayerMusic::volume = Volume;
			PlayerMusic::soundChannel -> setVolume (Volume);
		}

/*============================================================================================================*/

		// Set The Pan
		void PlayerMusic::SetPan (float Pan){

			PlayerMusic::pan = Pan;
			PlayerMusic::soundChannel -> setPan (Pan);
		}

/*============================================================================================================*/

		// Set The Pitch
		void PlayerMusic::SetPitch (float Pitch){

			PlayerMusic::pitch = Pitch;
			PlayerMusic::soundChannel -> setPitch (Pitch);
		}

/*============================================================================================================*/
/*------DESTRUCTOR--------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Destroy The Audio
		PlayerMusic::~PlayerMusic (){

			PlayerMusic::soundChannel -> stop ();
			PlayerMusic::soundStream  -> release ();
		}
	}
}
