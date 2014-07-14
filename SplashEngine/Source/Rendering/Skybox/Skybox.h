//============================================================================
// Name        : Skybox.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include "../../Base/Renderable.h"
#include <memory>
#include <string>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

		// Forward Declare Rendering Classes
		class Camera;
		class Texture;

/*============================================================================================================*/

		// The Skybox Class
		class Skybox : public base::Renderable{
		public:

			// Constructor / Destructor
			Skybox ();
			virtual ~Skybox ();

			// Functions
			bool Load (std::string PosX, std::string NegX,
					   std::string PosY, std::string NegY,
					   std::string PosZ, std::string NegZ, Material* Material);
			void Draw (Camera* Camera);

			// Variables - Buffers
			unsigned int arrayBuffer;
			unsigned int vertexBuffer;
			unsigned int indexBuffer;

			// Variables - Rendering
			std::shared_ptr <Texture> texture;
		};
	}
}