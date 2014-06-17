#pragma once

#include <memory>
#include <vector>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

		// Forward Declare Rendering Classes
		class Camera;
		class Line;
		class Material;
		class Skybox;
		class Texture;

/*============================================================================================================*/

		// The SceneManager Class
		class SceneManager{
		public:

			// Constructor / Destructor
			SceneManager ();
			virtual ~SceneManager ();

			// Functions - Adding Objects
			void Add (Line* Object);
			void Add (Skybox* Object);

			// Functions - Drawing
			void DrawAll (Camera* Camera, Material* PostPass);

			// Variables - Objects
			std::vector <Line*> lineList;
			std::vector <Skybox*> skyboxList;

			// Variables - GBuffer
			std::shared_ptr <Texture> textureGBuffer;
			unsigned int vertexGBuffer;
			unsigned int arrayGBuffer;
			unsigned int frameGBuffer;

		private:

			// Functions - Drawing
			void DrawGBuffer (Material* Material);
			void DrawSkybox (Camera* Camera);
		};
	}
}