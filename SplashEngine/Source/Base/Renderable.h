//============================================================================
// Name        : Renderable.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include "GameObject.h"

// The Splash Engine Namespace
namespace se{

	// Forward Declare Rendering Classes
	namespace rendering{

		class Camera;
		class Material;
	}

//============================================================================

	// The Base Namespace
	namespace base{

		// The Renderable Class
		class Renderable : public GameObject{
		public:

			// Functions
			virtual void Draw (rendering::Camera* Camera) {};

			// Variables
			rendering::Material* material;
		};
	}
}
