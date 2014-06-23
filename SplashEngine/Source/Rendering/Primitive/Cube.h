#pragma once

#include "../../Base/GameObject.h"

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

		// Forward Declare Camera and Material Class
		class Camera;
		class Material;

/*============================================================================================================*/

		// The Cube Class
		class Cube : public base::GameObject{
		public:

			// Constructor / Destructor
			~Cube ();

			// Functions
			bool Create (glm::vec3 Position, glm::vec3 Size, glm::vec3 Colour, Material* Material);
			void Draw (Camera* Camera);

			// Variables - Buffers
			unsigned int arrayBuffer;
			unsigned int vertexBuffer;
			unsigned int indexBuffer;

			// Variables - Misc
			Material* material;
			glm::vec3 colour;
		};
	}
}