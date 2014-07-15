//============================================================================
// Name        : Mesh.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include "../../Base/Renderable.h"
#include <memory>
#include <string>
#include <vector>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

		// Forward Declare Rendering Classes
		class Camera;
		class Texture;

/*============================================================================================================*/

		// The Mesh Vertex Struct
		struct Vertex{

			// Variables - Mesh Data
			glm::vec3 vertex;
			glm::vec3 normal;
			glm::vec3 tangent;
			glm::vec3 bitangent;
			glm::vec2 texCoord;
		};

/*============================================================================================================*/

		// The Mesh Data Struct
		struct MeshData{

			// Variables - Mesh Data
			std::vector <Vertex> vertexData;
			std::vector <unsigned int> indices;
			std::shared_ptr <Texture> texture;

			// Variables - Buffers
			unsigned int arrayBuffer;
			unsigned int vertexBuffer;
			unsigned int indexBuffer;
			unsigned int uvBuffer;
			unsigned int normalBuffer;
			unsigned int tangentBuffer;
			unsigned int bitangentBuffer;
		};

/*============================================================================================================*/

		// The Mesh Class
		class Mesh : public base::Renderable{
		public:

			// Constructor / Destructor
			virtual ~Mesh ();

			// Functions - Mesh Loading
			bool Load (glm::vec3 Position, std::string MeshPath, Material* Material);

			// Functions - Rendering
			virtual void Draw (Camera* Camera);

			// Variables
			std::vector <MeshData> meshData;

		private:

			// Functions - Mesh Loading
			bool GetMeshData (std::string MeshPath);
			bool GenBuffers ();
		};
	}
}
