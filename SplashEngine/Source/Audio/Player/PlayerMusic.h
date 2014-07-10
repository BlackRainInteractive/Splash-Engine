//============================================================================
// Name        : PlayerMusic.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include <string>

// Forward Declare FMOD Classes
namespace FMOD{

	class System;
	class Sound;
	class Channel;
}

/*============================================================================================================*/

// The Splash Engine Namespace
namespace se{

	// The Audio Namespace
	namespace audio{

		// The Music Player Class
		class PlayerMusic{
		public:

			// Constructor / Destructor
			virtual ~PlayerMusic ();

			// Functions - Audio Loading
			virtual bool Load (std::string AudioPath, bool Loop = true);

			// Functions - Playback Controls
			virtual bool Play ();
			virtual void Pause ();
			virtual void Stop ();
			virtual void SetVolume (float Volume);
			virtual void SetPan (float Pan);
			virtual void SetPitch (float Pitch);

			// Variables
			bool loop;
			float volume;
			float pan;
			float pitch;
			static FMOD::System* soundSystem;

		protected:

			// Variables
			FMOD::Sound* soundStream;
			FMOD::Channel* soundChannel;
		};
	}
}