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

		// The Mesh Data Struct
		struct MeshData{

			// Variables - Mesh Data
			std::vector <glm::vec3> vertices;
			std::vector <glm::vec3> normals;
			std::vector <glm::vec3> tangents;
			std::vector <glm::vec3> bitangents;
			std::vector <glm::vec2> texCoord1;
			std::vector <glm::vec2> texCoord2;
			std::vector <unsigned int> indices;

			// Variables - Buffers
			unsigned int arrayBuffer;
			unsigned int vertexBuffer;
			unsigned int indexBuffer;
			unsigned int uvBuffer1;
			unsigned int uvBuffer2;
			unsigned int normalBuffer;
			unsigned int tangentBuffer;
			unsigned int bitangentBuffer;

			// Variables - Texture
			std::shared_ptr <Texture> texture;
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