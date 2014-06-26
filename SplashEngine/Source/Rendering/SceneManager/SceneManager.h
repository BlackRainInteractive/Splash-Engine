#pragma once

#include <memory>
#include <vector>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

		// Forward Declare Rendering Classes
		class Camera;
		class Cube;
		class Grid;
		class GUI;
		class Line;
		class Material;
		class Skybox;
		class Sphere;
		class Texture;

/*============================================================================================================*/

		// The SceneManager Class
		class SceneManager{
		public:

			// Constructor / Destructor
			SceneManager ();
			virtual ~SceneManager ();

			// Functions - Adding Objects
			void Add (Cube* Object);
			void Add (Grid* Object);
			void Add (GUI* Object);
			void Add (Line* Object);
			void Add (Skybox* Object);
			void Add (Sphere* Object);

			// Functions - Drawing
			void DrawAll (Camera* Camera, Material* PostPass);

			// Variables - Objects
			std::vector <Cube*> cubeList;
			std::vector <Grid*> gridList;
			std::vector <GUI*> guiList;
			std::vector <Line*> lineList;
			std::vector <Skybox*> skyboxList;
			std::vector <Sphere*> sphereList;

			// Variables - GBuffer
			std::shared_ptr <Texture> textureGBuffer;
			unsigned int vertexGBuffer;
			unsigned int arrayGBuffer;
			unsigned int frameGBuffer;

		private:

			// Functions - Drawing
			void DrawGBuffer (Material* Material);
			void DrawPrimitives (Camera* Camera);
			void DrawSkybox (Camera* Camera);
		};
	}
}