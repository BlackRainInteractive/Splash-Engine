//============================================================================
// Name        : Mesh.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "Mesh.h"
#include "../../Utility/DebugLog/DebugLog.h"
#include "../Camera/Camera.h"
#include "../Material/Material.h"
#include "../Texture/Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <GL/glew.h>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Load The Mesh From A File
		bool Mesh::Load (glm::vec3 Position, std::string MeshPath, Material* Material){

			// Set The Mesh Variables
			Mesh::position = Position;
			Mesh::rotation = glm::vec3 (0);
			Mesh::scale	   = glm::vec3 (1);
			Mesh::material = Material;
			Mesh::parent   = nullptr;

			// Transform Mesh To Start Position
			Mesh::Transform (Mesh::position, Mesh::rotation, Mesh::scale);

			// Load The Mesh And Gen Buffers
			if (!Mesh::GetMeshData (MeshPath) || !Mesh::GenBuffers ())
				return false;

			// Return Success
			return true;
		}

/*============================================================================================================*/

		// Draw The Mesh
		void Mesh::Draw (Camera* Camera){

			// Set The Matrix Transforms
			Mesh::material -> SetUniform ("M", Mesh::GetParentTransforms () * Mesh::mMatrix);
			Mesh::material -> SetUniform ("V", Camera -> vMatrix);
			Mesh::material -> SetUniform ("P", Camera -> pMatrix);

			// Bind The Material
			Mesh::material -> Bind (true);

			// Loop Through Meshes
			for (unsigned int i = 0; i < Mesh::meshData.size (); ++i){

				// Pass Texture Data
				Mesh::meshData [i].texture -> BindAll (Mesh::material);

				// Bind VAO And Draw
				glBindVertexArray (Mesh::meshData [i].arrayBuffer);
					glDrawElements (GL_TRIANGLES, Mesh::meshData [i].indices.size (), GL_UNSIGNED_INT, nullptr);
				glBindVertexArray (0);
			}

			// Unbind Material
			Mesh::material -> Bind (false);
		}

/*============================================================================================================*/
/*------PRIVATE FUNCTIONS-------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Load The Mesh Data
		bool Mesh::GetMeshData (std::string MeshPath){

			// Create The Mesh Importer
			Assimp::Importer importer;

			// Load Mesh From File
			const aiScene* scene = importer.ReadFile (MeshPath, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_CalcTangentSpace);

			// Check For Errors
			if (!scene){

				utility::DebugLog::WriteLog ("Could not load mesh " + MeshPath, LOG_TYPE::WARNING);
				return false;
			}

			// Loop Through All Meshes
			for (unsigned int m = 0; m < scene -> mNumMeshes; ++m){

				// Create Mesh Data
				MeshData meshData;

				// Get Mesh From Index And Create Mesh Struct
				const aiMesh* mesh = scene -> mMeshes [m];

				// Get Vertex Data
				for (unsigned int i = 0; i < mesh -> mNumVertices; ++i){

					// Create Vertex Data
					Vertex vertex;

					// Vertices
					aiVector3D vertAttribute = mesh -> mVertices [i];
					vertex.vertex = (glm::vec3 (vertAttribute.x, vertAttribute.y, vertAttribute.z));

					// Tex Coords
					if (mesh -> HasTextureCoords (0)){

						vertAttribute = mesh -> mTextureCoords [0][i];
						vertex.texCoord = (glm::vec2 (vertAttribute.x, vertAttribute.y));
					}

					else
						vertex.texCoord = (glm::vec2 (0));

					// Normals
					if (mesh -> HasNormals ()){

						vertAttribute = mesh -> mNormals [i];
						vertex.normal = (glm::vec3 (vertAttribute.x, vertAttribute.y, vertAttribute.z));
					}

					else
						vertex.normal = (glm::vec3 (0));

					// Tangents And Bitangents
					if (mesh -> HasTangentsAndBitangents ()){

						// Tangents
						vertAttribute = mesh -> mTangents [i];
						vertex.tangent = (glm::vec3 (vertAttribute.x, vertAttribute.y, vertAttribute.z));

						// Bitangents
						vertAttribute = mesh -> mBitangents [i];
						vertex.bitangent = (glm::vec3 (vertAttribute.x, vertAttribute.y, vertAttribute.z));
					}

					else{

						vertex.tangent = (glm::vec3 (0));
						vertex.bitangent = (glm::vec3 (0));
					}

					// Add Vertex To Mesh Class
					meshData.vertexData.push_back (vertex);
				}

				// Get Indices
				for (unsigned int i = 0; i < mesh -> mNumFaces; ++i){

					meshData.indices.push_back (mesh -> mFaces [i].mIndices [0]);
					meshData.indices.push_back (mesh -> mFaces [i].mIndices [1]);
					meshData.indices.push_back (mesh -> mFaces [i].mIndices [2]);
				}

				// Create New Texture
				aiString texPath;
				meshData.texture = std::shared_ptr <Texture> (new Texture);

				// Get Diffuse Texture
				if (!scene -> mMaterials [mesh -> mMaterialIndex] -> GetTexture (aiTextureType_DIFFUSE, 0, &texPath))
					meshData.texture -> Load (texPath.C_Str (), "DiffuseTexture");

				// Add Data To Mesh Class
				Mesh::meshData.push_back (meshData);
			}

			// Free The Scene
			importer.FreeScene ();

			// Return Success
			return true;
		}

/*============================================================================================================*/

		// Generate The Buffers
		bool Mesh::GenBuffers (){

			// Look Through All Meshes
			for (unsigned int i = 0; i < Mesh::meshData.size (); ++i){

				std::vector <glm::vec3> vertexList;
				std::vector <glm::vec3> normalList;
				std::vector <glm::vec3> tangentList;
				std::vector <glm::vec3> bitangentList;
				std::vector <glm::vec2> texCoordList;

				// Build Data Lists
				for (auto object : Mesh::meshData [i].vertexData){

					vertexList.push_back    (object.vertex);
					texCoordList.push_back  (object.texCoord);
					normalList.push_back    (object.normal);
					tangentList.push_back   (object.tangent);
					bitangentList.push_back (object.bitangent);
				}

				// Create And Bind The VAO
				glGenVertexArrays (1, &Mesh::meshData [i].arrayBuffer);
				glBindVertexArray (Mesh::meshData [i].arrayBuffer);

				// Gen All Buffers
				glGenBuffers (1, &Mesh::meshData [i].vertexBuffer);
				glGenBuffers (1, &Mesh::meshData [i].indexBuffer);
				glGenBuffers (1, &Mesh::meshData [i].uvBuffer);
				glGenBuffers (1, &Mesh::meshData [i].normalBuffer);
				glGenBuffers (1, &Mesh::meshData [i].tangentBuffer);
				glGenBuffers (1, &Mesh::meshData [i].bitangentBuffer);

				// Create Vertex Buffer
				glBindBuffer (GL_ARRAY_BUFFER, Mesh::meshData [i].vertexBuffer);
				glBufferData (GL_ARRAY_BUFFER, vertexList.size () * sizeof (glm::vec3), &vertexList [0], GL_STATIC_DRAW);
				glEnableVertexAttribArray (0);
				glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Create UV Buffers
				glBindBuffer (GL_ARRAY_BUFFER, Mesh::meshData [i].uvBuffer);
				glBufferData (GL_ARRAY_BUFFER, texCoordList.size () * sizeof (glm::vec2), &texCoordList [0], GL_STATIC_DRAW);
				glEnableVertexAttribArray (1);
				glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Create Normal Buffer
				glBindBuffer (GL_ARRAY_BUFFER, Mesh::meshData [i].normalBuffer);
				glBufferData (GL_ARRAY_BUFFER, normalList.size () * sizeof (glm::vec3), &normalList [0], GL_STATIC_DRAW);
				glEnableVertexAttribArray (2);
				glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Create Tangent Buffer
				glBindBuffer (GL_ARRAY_BUFFER, Mesh::meshData [i].tangentBuffer);
				glBufferData (GL_ARRAY_BUFFER, tangentList.size () * sizeof (glm::vec3), &tangentList [0], GL_STATIC_DRAW);
				glEnableVertexAttribArray (3);
				glVertexAttribPointer (3, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Create Bitangent Buffer
				glBindBuffer (GL_ARRAY_BUFFER, Mesh::meshData [i].bitangentBuffer);
				glBufferData (GL_ARRAY_BUFFER, bitangentList.size () * sizeof (glm::vec3), &bitangentList [0], GL_STATIC_DRAW);
				glEnableVertexAttribArray (4);
				glVertexAttribPointer (4, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Create Index Buffer
				glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, Mesh::meshData [i].indexBuffer);
				glBufferData (GL_ELEMENT_ARRAY_BUFFER, Mesh::meshData [i].indices.size () * sizeof (unsigned int), &Mesh::meshData [i].indices [0], GL_STATIC_DRAW);

				// Unbind Vertex Array
				glBindVertexArray (0);
			}

			// Return Success
			return true;
		}

/*============================================================================================================*/
/*------DESTRUCTOR--------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Destroy The Mesh
		Mesh::~Mesh (){

			// Loop Through All Meshes
			for (unsigned int i = 0; i < Mesh::meshData.size (); ++i){

				glDeleteVertexArrays (1, &Mesh::meshData [i].arrayBuffer);
				glDeleteBuffers (1, &Mesh::meshData [i].vertexBuffer);
				glDeleteBuffers (1, &Mesh::meshData [i].indexBuffer);
				glDeleteBuffers (1, &Mesh::meshData [i].uvBuffer);
				glDeleteBuffers (1, &Mesh::meshData [i].normalBuffer);
				glDeleteBuffers (1, &Mesh::meshData [i].tangentBuffer);
				glDeleteBuffers (1, &Mesh::meshData [i].bitangentBuffer);
			}
		}
	}
}
