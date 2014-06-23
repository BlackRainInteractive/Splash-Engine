#pragma once

#include "../../Base/GameObject.h"
#include <vector>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

		// Forward Declare Camera and Material Class
		class Camera;
		class Material;

/*============================================================================================================*/

		// The Sphere Class
		class Sphere : public base::GameObject{
		public:

			// Constructor / Destructor
			~Sphere ();

			// Functions
			bool Create (glm::vec3 Position, float Radius, int Slices, int Stacks, glm::vec3 Colour, Material* Material);
			void Draw (Camera* Camera);

			// Variables - Buffers
			unsigned int arrayBuffer;
			unsigned int vertexBuffer;
			unsigned int indexBuffer;

			// Variables - Lists
			std::vector <glm::vec3> vertexBufferData;
			std::vector <unsigned int> indexBufferData;

			// Variables - Misc
			Material* material;
			glm::vec3 colour;
		};
	}
}