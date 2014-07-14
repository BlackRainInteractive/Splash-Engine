//============================================================================
// Name        : Grid.h
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

		// The Grid Class
		class Grid : public base::Renderable{
		public:

			// Constructor / Destructor
			~Grid ();

			// Functions
			bool Create (glm::vec3 Position, int GridCount, glm::vec3 Colour, Material* Material);
			virtual void Draw (Camera* Camera);

			// Variables - Buffers
			unsigned int arrayBuffer;
			unsigned int vertexBuffer;

			// Variables - Vertices
			std::vector <glm::vec3> vertexList;

			// Variables - Misc
			glm::vec3 colour;
		};
	}
}
