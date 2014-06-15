#pragma once

#include "../../Base/GameObject.h"
#include <memory>
#include <string>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

		// Forward Declare Material, Texture, And Camera Class
		class Material;
		class Texture;
		class Camera;

/*============================================================================================================*/

		// The Skybox Class
		class Skybox : public base::GameObject{
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
			Material* material;
		};
	}
}