#include "Mesh.h"
#include "../Camera/Camera.h"
#include "../Material/Material.h"
#include "../Texture/Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <GL/glew.h>
#include <iostream>

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

			// Loop Through Mesh Data
			for (unsigned int i = 0; i < Mesh::meshData.size (); ++i){

				// Pass Texture Data
				Mesh::meshData[i].texture -> BindAll (Mesh::material);

				// Bind VAO And Draw
				glBindVertexArray (Mesh::meshData[i].arrayBuffer);
					glDrawElements (GL_TRIANGLES, Mesh::meshData[i].indices.size (), GL_UNSIGNED_INT, nullptr);
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

				std::cout << "ERROR: Could not load mesh " << MeshPath << '\n';
				return false;
			}

			// Loop Through All Meshes
			for (unsigned int m = 0; m < scene -> mNumMeshes; ++m){

				// Get Mesh From Index And Create Mesh Struct
				const aiMesh* mesh = scene -> mMeshes [m];
				MeshData meshInfo;

				// Get Vertex Data
				for (unsigned int i = 0; i < mesh -> mNumVertices; ++i){

					// Vertices
					aiVector3D vertAttribute = mesh -> mVertices [i];
					meshInfo.vertices.push_back (glm::vec3 (vertAttribute.x, vertAttribute.y, vertAttribute.z));

					// UV1
					if (mesh -> HasTextureCoords (0)){

						vertAttribute = mesh -> mTextureCoords [0][i];
						meshInfo.texCoord1.push_back (glm::vec2 (vertAttribute.x, vertAttribute.y));
					}

					else
						meshInfo.texCoord1.push_back (glm::vec2 (0));

					// UV2
					if (mesh -> HasTextureCoords (1)){

						vertAttribute = mesh -> mTextureCoords [1][i];
						meshInfo.texCoord2.push_back (glm::vec2 (vertAttribute.x, vertAttribute.y));
					}

					else
						meshInfo.texCoord2.push_back (glm::vec2 (0));

					// Normals
					if (mesh -> HasNormals ()){

						vertAttribute = mesh -> mNormals [i];
						meshInfo.normals.push_back (glm::vec3 (vertAttribute.x, vertAttribute.y, vertAttribute.z));
					}

					else
						meshInfo.normals.push_back (glm::vec3 (0));

					// Tangents And Bitangents
					if (mesh -> HasTangentsAndBitangents ()){

						// Tangents
						vertAttribute = mesh -> mTangents [i];
						meshInfo.tangents.push_back (glm::vec3 (vertAttribute.x, vertAttribute.y, vertAttribute.z));

						// Bitangents
						vertAttribute = mesh -> mBitangents [i];
						meshInfo.bitangents.push_back (glm::vec3 (vertAttribute.x, vertAttribute.y, vertAttribute.z));
					}

					else{

						meshInfo.tangents.push_back (glm::vec3 (0));
						meshInfo.bitangents.push_back (glm::vec3 (0));
					}
				}

				// Get Indices
				for (unsigned int i = 0; i < mesh -> mNumFaces; ++i){

					meshInfo.indices.push_back (mesh -> mFaces [i].mIndices [0]);
					meshInfo.indices.push_back (mesh -> mFaces [i].mIndices [1]);
					meshInfo.indices.push_back (mesh -> mFaces [i].mIndices [2]);
				}

				// Create New Texture
				aiString texPath;
				meshInfo.texture = std::shared_ptr <Texture> (new Texture);

				// Get Diffuse Texture
				if (!scene -> mMaterials [mesh -> mMaterialIndex] -> GetTexture (aiTextureType_DIFFUSE, 0, &texPath))
					meshInfo.texture -> Load (texPath.C_Str (), "DiffuseTexture");

				// Add Mesh Data To Mesh Class
				Mesh::meshData.push_back (meshInfo);
			}

			// Free The Scene
			importer.FreeScene ();

			// Return Success
			return true;
		}

/*============================================================================================================*/

		// Generate The Buffers
		bool Mesh::GenBuffers (){

			// Loop Through Each Mesh
			for (unsigned int i = 0; i < Mesh::meshData.size (); ++i){

				// Create And Bind The VAO
				glGenVertexArrays (1, &Mesh::meshData[i].arrayBuffer);
				glBindVertexArray (Mesh::meshData[i].arrayBuffer);

				// Gen All Buffers
				glGenBuffers (1, &Mesh::meshData[i].vertexBuffer);
				glGenBuffers (1, &Mesh::meshData[i].indexBuffer);
				glGenBuffers (1, &Mesh::meshData[i].uvBuffer1);
				glGenBuffers (1, &Mesh::meshData[i].uvBuffer2);
				glGenBuffers (1, &Mesh::meshData[i].normalBuffer);
				glGenBuffers (1, &Mesh::meshData[i].tangentBuffer);
				glGenBuffers (1, &Mesh::meshData[i].bitangentBuffer);

				// Create Vertex Buffer
				glBindBuffer (GL_ARRAY_BUFFER, Mesh::meshData[i].vertexBuffer);
				glBufferData (GL_ARRAY_BUFFER, Mesh::meshData[i].vertices.size () * sizeof (glm::vec3), &Mesh::meshData[i].vertices [0], GL_STATIC_DRAW);
				glEnableVertexAttribArray (0);
				glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Create UV Buffer1
				glBindBuffer (GL_ARRAY_BUFFER, Mesh::meshData[i].uvBuffer1);
				glBufferData (GL_ARRAY_BUFFER, Mesh::meshData[i].texCoord1.size () * sizeof (glm::vec2), &Mesh::meshData[i].texCoord1 [0], GL_STATIC_DRAW);
				glEnableVertexAttribArray (1);
				glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Create UV Buffer2
				glBindBuffer (GL_ARRAY_BUFFER, Mesh::meshData[i].uvBuffer2);
				glBufferData (GL_ARRAY_BUFFER, Mesh::meshData[i].texCoord2.size () * sizeof (glm::vec2), &Mesh::meshData[i].texCoord2 [0], GL_STATIC_DRAW);
				glEnableVertexAttribArray (2);
				glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Create Normal Buffer
				glBindBuffer (GL_ARRAY_BUFFER, Mesh::meshData[i].normalBuffer);
				glBufferData (GL_ARRAY_BUFFER, Mesh::meshData[i].normals.size () * sizeof (glm::vec3), &Mesh::meshData[i].normals [0], GL_STATIC_DRAW);
				glEnableVertexAttribArray (3);
				glVertexAttribPointer (3, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Create Tangent Buffer
				glBindBuffer (GL_ARRAY_BUFFER, Mesh::meshData[i].tangentBuffer);
				glBufferData (GL_ARRAY_BUFFER, Mesh::meshData[i].tangents.size () * sizeof (glm::vec3), &Mesh::meshData[i].tangents [0], GL_STATIC_DRAW);
				glEnableVertexAttribArray (4);
				glVertexAttribPointer (4, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Create Bitangent Buffer
				glBindBuffer (GL_ARRAY_BUFFER, Mesh::meshData[i].bitangentBuffer);
				glBufferData (GL_ARRAY_BUFFER, Mesh::meshData[i].bitangents.size () * sizeof (glm::vec3), &Mesh::meshData[i].bitangents [0], GL_STATIC_DRAW);
				glEnableVertexAttribArray (5);
				glVertexAttribPointer (5, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Create Index Buffer
				glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, Mesh::meshData[i].indexBuffer);
				glBufferData (GL_ELEMENT_ARRAY_BUFFER, Mesh::meshData[i].indices.size () * sizeof (unsigned int), &Mesh::meshData[i].indices[0], GL_STATIC_DRAW);

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

			for (unsigned int i = 0; i < Mesh::meshData.size (); ++i){

				glDeleteVertexArrays (1, &Mesh::meshData[i].arrayBuffer);
				glDeleteBuffers (1, &Mesh::meshData[i].vertexBuffer);
				glDeleteBuffers (1, &Mesh::meshData[i].indexBuffer);
				glDeleteBuffers (1, &Mesh::meshData[i].uvBuffer1);
				glDeleteBuffers (1, &Mesh::meshData[i].uvBuffer2);
				glDeleteBuffers (1, &Mesh::meshData[i].normalBuffer);
				glDeleteBuffers (1, &Mesh::meshData[i].tangentBuffer);
				glDeleteBuffers (1, &Mesh::meshData[i].bitangentBuffer);
			}
		}
	}
}