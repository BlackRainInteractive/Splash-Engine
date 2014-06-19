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

		// The Grid Class
		class Grid : public base::GameObject{
		public:

			// Constructor / Destructor
			~Grid ();

			// Functions
			bool Create (glm::vec3 Position, int GridCount, glm::vec3 Colour, Material* Material);
			void Draw (Camera* Camera);

			// Variables - Buffers
			unsigned int arrayBuffer;
			unsigned int vertexBuffer;

			// Variables - Vertices
			std::vector <glm::vec3> vertexList;

			// Variables - Misc
			Material* material;
			glm::vec3 colour;
		};
	}
}