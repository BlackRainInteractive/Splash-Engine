//============================================================================
// Name        : SceneManager.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include <memory>
#include <vector>

// The Splash Engine Namespace
namespace se{

	// Forward Declare Renderable Class
	namespace base{
		class Renderable;
	}

/*============================================================================================================*/

	// Forward Declare Batch Group Class
	namespace optimization{
		class BatchGroup;
	}

/*============================================================================================================*/

	// The Rendering Namespace
	namespace rendering{

		// Forward Declare Rendering Classes
		class Camera;
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
			void Add (base::Renderable* Object);
			void Add (optimization::BatchGroup* Object);
			void Add (Skybox* Object);

			// Functions - Removing Objects
			void Remove (base::Renderable* Object);
			void Remove (optimization::BatchGroup* Object);
			void Remove (Skybox* Object);

			// Functions - Drawing
			void DrawAll (Camera* Camera, Material* PostPass);

			// Variables - Objects
			std::vector <base::Renderable*> renderableList;
			std::vector <optimization::BatchGroup*> batchGroupList;
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
			void DrawBatchGroups (Camera* Camera);
			void DrawRenderables (Camera* Camera);
		};
	}
}
