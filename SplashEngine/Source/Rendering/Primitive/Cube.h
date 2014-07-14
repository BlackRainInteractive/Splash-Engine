//============================================================================
// Name        : Cube.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include "../../Base/Renderable.h"

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

		// Forward Declare Camera Class
		class Camera;

/*============================================================================================================*/

		// The Cube Class
		class Cube : public base::Renderable{
		public:

			// Constructor / Destructor
			~Cube ();

			// Functions
			bool Create (glm::vec3 Position, glm::vec3 Size, glm::vec3 Colour, Material* Material);
			virtual void Draw (Camera* Camera);

			// Variables - Buffers
			unsigned int arrayBuffer;
			unsigned int vertexBuffer;
			unsigned int indexBuffer;

			// Variables - Misc
			glm::vec3 colour;
		};
	}
}