//============================================================================
// Name        : Player3D.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include "PlayerMusic.h"
#include "../../Base/GameObject.h"

// The Splash Engine Namespace
namespace se{

	// Forward Declare Rendering Classes
	namespace rendering{
		class Camera;
	}

//============================================================================

	// The Audio Namespace
	namespace audio{

		// The 3D Player Class
		class Player3D : public base::GameObject, public PlayerMusic{
		public:

			// Functions
			bool Load (std::string AudioPath, bool Loop = false);
			void Update (rendering::Camera* Camera);
		};
	}
}