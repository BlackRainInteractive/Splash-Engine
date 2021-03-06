//============================================================================
// Name        : Line.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include "../../Base/Renderable.h"
#include <glm/glm.hpp>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

		// Forward Declare Camera and Material Class
		class Camera;

/*============================================================================================================*/

		// The Line Class
		class Line : public base::Renderable{
		public:

			// Constructor / Destructor
			virtual ~Line ();

			// Functions
			bool Create (glm::vec3 StartPos, glm::vec3 EndPos, glm::vec3 Colour, Material* Material);
			void Transform (glm::vec3 StartPos, glm::vec3 EndPos);
			void Draw (Camera* Camera);

			// Variables - Buffers
			unsigned int arrayBuffer;
			unsigned int vertexBuffer;

			// Variables - Misc
			glm::vec3 startPos;
			glm::vec3 endPos;
			glm::vec3 colour;
		};
	}
}
