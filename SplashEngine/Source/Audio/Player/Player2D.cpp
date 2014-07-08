#include "Player2D.h"
#include <FMOD/fmod.hpp>
#include <iostream>

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

				std::cout << "ERROR: Could not load audio '" <<  AudioPath << "'\n";
				return false;
			}

			// Return Success
			return true;
		}
	}
}