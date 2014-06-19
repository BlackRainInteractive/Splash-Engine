#include "Skybox.h"
#include "../Camera/Camera.h"
#include "../Material/Material.h"
#include "../Texture/Texture.h"
#include <GL/glew.h>
#include <iostream>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

/*============================================================================================================*/
/*------CONSTRUCTOR-------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// The Default Skybox Constructor
		Skybox::Skybox (){

			// Set Variables
			Skybox::parent = nullptr;

			// Create A New Texture
			Skybox::texture = std::shared_ptr <Texture> (new Texture);

			// Create The Skybox Vert Data
			const float vertexBufferData [] = {-0.5f, -0.5f, -0.5f,
											    0.5f, -0.5f, -0.5f,
											    0.5f,  0.5f, -0.5f,
											   -0.5f,  0.5f, -0.5f,
											   -0.5f, -0.5f,  0.5f,
											    0.5f, -0.5f,  0.5f,
											    0.5f,  0.5f,  0.5f,
											   -0.5f,  0.5f,  0.5f};

			// Create The Skybox Index Data
			const unsigned int indexBufferData [] = {0, 4, 5,
													 5, 1, 0,
													 3, 6, 7,
													 3, 2, 6,
													 7, 6, 4,
													 6, 5, 4,
													 2, 3, 1,
													 3, 0, 1,
													 3, 7, 0,
													 7, 4, 0,
													 6, 2, 5,
													 2, 1, 5};

			// Create And Bind The VAO
			glGenVertexArrays (1, &arrayBuffer);
			glBindVertexArray (Skybox::arrayBuffer);

			// Gen And Bind The Vertex Buffer
			glGenBuffers (1, &vertexBuffer);
			glBindBuffer (GL_ARRAY_BUFFER, Skybox::vertexBuffer);

			// Buffer The Vertex Data
			glBufferData (GL_ARRAY_BUFFER, sizeof (vertexBufferData), &vertexBufferData, GL_STATIC_DRAW);
			glEnableVertexAttribArray (0);
			glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

			// Gen And Bind The Index Buffer
			glGenBuffers (1, &indexBuffer);
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, Skybox::indexBuffer);
			glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (indexBufferData), &indexBufferData, GL_STATIC_DRAW);

			// Unbind The VAO
			glBindVertexArray (0);

			// Set The Skybox Transform
			Skybox::Transform (glm::vec3 (0), glm::vec3 (0));
		}

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Load The Skybox Textures And Material
		bool Skybox::Load (std::string PosX, std::string NegX,
						   std::string PosY, std::string NegY,
					       std::string PosZ, std::string NegZ, Material* Material){

			// Set The Material
			Skybox::material = Material;
			
			// Load The Textures
			if (!Skybox::texture -> Load (PosX, NegX, PosY, NegY, PosZ, NegZ, "DiffuseTexture")){

				std::cout << "ERROR: Could not create the Skybox.\n";
				return false;
			}

			return true;
		}

/*============================================================================================================*/

		// Draw The Skybox
		void Skybox::Draw (Camera* Camera){

			// Move Skybox To Camera Position
			Skybox::Transform (Camera -> position, Skybox::rotation);

			// Set The Matrix Transforms
			Skybox::material -> SetUniform ("M", Skybox::mMatrix);
			Skybox::material -> SetUniform ("V", Camera -> vMatrix);
			Skybox::material -> SetUniform ("P", Camera -> pMatrix);

			// Bind The Material
			Skybox::material -> Bind (true);

			// Bind The Texture
			Skybox::texture -> BindAll (Skybox::material);

			// Bind VAO And Draw
			glBindVertexArray (Skybox::arrayBuffer);
			glDrawElements (GL_TRIANGLES, 9 * sizeof (unsigned int), GL_UNSIGNED_INT, nullptr);
			glBindVertexArray (0);

			// Unbind Material
			Skybox::material -> Bind (false);
		}

/*============================================================================================================*/
/*------DESTRUCTOR--------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Destroy The Skybox
		Skybox::~Skybox (){

			glDeleteVertexArrays (1, &arrayBuffer);
			glDeleteBuffers		 (1, &vertexBuffer);
			glDeleteBuffers		 (1, &indexBuffer);
		}
	}
}