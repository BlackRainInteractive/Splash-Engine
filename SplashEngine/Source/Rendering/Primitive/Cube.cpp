//============================================================================
// Name        : Cube.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "Cube.h"
#include "../../Window/Window.h"
#include "../Camera/Camera.h"
#include "../Material/Material.h"
#include <GL/glew.h>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Create The Cube
		bool Cube::Create (glm::vec3 Position, glm::vec3 Size, glm::vec3 Colour, Material* Material){

			// Set The Cube Variables
			Cube::position = Position;
			Cube::rotation = glm::vec3 (0);
			Cube::scale	   = glm::vec3 (1);
			Cube::colour   = Colour;
			Cube::material = Material;
			Cube::parent   = nullptr;

			glm::vec3 halfSize = Size * 0.5f;

			// Set The Cube Model Matrix
			Cube::Transform (Cube::position, Cube::rotation, Cube::scale);

			// Create Cube Verts
			const glm::vec3 vertexBufferData[] = {glm::vec3 (-halfSize.x, -halfSize.y,  halfSize.z),
												  glm::vec3 (-halfSize.x, -halfSize.y, -halfSize.z),
												  glm::vec3 ( halfSize.x, -halfSize.y, -halfSize.z),
												  glm::vec3 ( halfSize.x, -halfSize.y,  halfSize.z),
												  glm::vec3 (-halfSize.x,  halfSize.y,  halfSize.z),
												  glm::vec3 (-halfSize.x,  halfSize.y, -halfSize.z),
												  glm::vec3 ( halfSize.x,  halfSize.y, -halfSize.z),
												  glm::vec3 ( halfSize.x,  halfSize.y,  halfSize.z)};

			// Create Cube Indices
			const unsigned int indexBufferData[] = {0, 4, 5,
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
			glBindVertexArray (Cube::arrayBuffer);

			// Gen And Bind The Vertex Buffer
			glGenBuffers (1, &vertexBuffer);
			glBindBuffer (GL_ARRAY_BUFFER, Cube::vertexBuffer);

			// Buffer The Vertex Data
			glBufferData (GL_ARRAY_BUFFER, sizeof (vertexBufferData), &vertexBufferData, GL_STATIC_DRAW);
			glEnableVertexAttribArray (0);
			glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

			// Gen And Bind The Index Buffer
			glGenBuffers (1, &indexBuffer);
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, Cube::indexBuffer);
			glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (indexBufferData), &indexBufferData, GL_STATIC_DRAW);

			// Unbind The VAO
			glBindVertexArray (0);

			return true;
		}

/*============================================================================================================*/

		// Draw The Cube
		void Cube::Draw (Camera* Camera){

			// Set The Matrix Transforms
			Cube::material -> SetUniform ("M", Cube::GetParentTransforms () * Cube::mMatrix);
			Cube::material -> SetUniform ("V", Camera -> vMatrix);
			Cube::material -> SetUniform ("P", Camera -> pMatrix);
			Cube::material -> SetUniform ("VP", Window::vpMatrix);

			// Set Line Colour
			Cube::material -> SetUniform ("Colour", Cube::colour);

			// Bind The Material
			Cube::material -> Bind (true);

			// Bind VAO And Draw
			glBindVertexArray (Cube::arrayBuffer);
				glDrawElements (GL_TRIANGLES, 9 * sizeof (unsigned int), GL_UNSIGNED_INT, nullptr);
			glBindVertexArray (0);

			// Unbind Material
			Cube::material -> Bind (false);
		}

/*============================================================================================================*/
/*------DESTRUCTOR--------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Destroy The Cube
		Cube::~Cube (){

			glDeleteVertexArrays (1, &arrayBuffer);
			glDeleteBuffers		 (1, &vertexBuffer);
			glDeleteBuffers		 (1, &indexBuffer);
		}
	}
}