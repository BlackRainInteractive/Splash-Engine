//============================================================================
// Name        : Sphere.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include "../../Base/Renderable.h"
#include <vector>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

		// Forward Declare Camera Class
		class Camera;

/*============================================================================================================*/

		// The Sphere Class
		class Sphere : public base::Renderable{
		public:

			// Constructor / Destructor
			~Sphere ();

			// Functions
			bool Create (glm::vec3 Position, float Radius, int Slices, int Stacks, glm::vec3 Colour, Material* Material);
			virtual void Draw (Camera* Camera);

			// Variables - Buffers
			unsigned int arrayBuffer;
			unsigned int vertexBuffer;
			unsigned int indexBuffer;

			// Variables - Lists
			std::vector <glm::vec3> vertexBufferData;
			std::vector <unsigned int> indexBufferData;

			// Variables - Misc
			glm::vec3 colour;
		};
	}
}
