//============================================================================
// Name        : Player2D.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include "PlayerMusic.h"

// The Splash Engine Namespace
namespace se{

	// The Audio Namespace
	namespace audio{

		// The 2D Player Class
		class Player2D : public PlayerMusic{
		public:

			// Functions - Audio Loading
			bool Load (std::string AudioPath, bool Loop = true);
		};
	}
}