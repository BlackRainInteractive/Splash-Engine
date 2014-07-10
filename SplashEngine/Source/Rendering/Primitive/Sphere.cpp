//============================================================================
// Name        : Sphere.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "Sphere.h"
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

		// Create The Sphere
		bool Sphere::Create (glm::vec3 Position, float Radius, int Slices, int Stacks, glm::vec3 Colour, Material* Material){

			// Set The Sphere Variables
			Sphere::position = Position;
			Sphere::rotation = glm::vec3 (0);
			Sphere::scale	 = glm::vec3 (1);
			Sphere::colour   = Colour;
			Sphere::material = Material;
			Sphere::parent   = nullptr;

			// Set The Sphere Model Matrix
			Sphere::Transform (Sphere::position, Sphere::rotation, Sphere::scale);

			// Calc The Vertices
			for (int i = 0; i <= Stacks; ++i){

				float V   = i / (float) Stacks;
				float phi = V * glm::pi <float> ();

				// Loop Through Slices
				for (int j = 0; j <= Slices; ++j){

					float U = j / (float) Slices;
					float theta = U * (glm::pi <float> () * 2);

					// Calc The Vertex Postions
					float x = cosf (theta) * sinf (phi);
					float y = cosf (phi);
					float z = sinf (theta) * sinf (phi);

					// Push Back Vertex Data
					Sphere::vertexBufferData.push_back (glm::vec3 (x, y, z) * Radius);
				}
			}

			// Calc The Index Positions
			for (int i = 0; i < Slices * Stacks + Slices; ++i){

				Sphere::indexBufferData.push_back (i);
			    Sphere::indexBufferData.push_back (i + Slices + 1);
			    Sphere::indexBufferData.push_back (i + Slices);
			 
			    Sphere::indexBufferData.push_back (i + Slices + 1);
			    Sphere::indexBufferData.push_back (i);
			    Sphere::indexBufferData.push_back (i + 1);
			}

			// Create And Bind The VAO
			glGenVertexArrays (1, &arrayBuffer);
			glBindVertexArray (Sphere::arrayBuffer);

			// Gen And Bind The Vertex Buffer
			glGenBuffers (1, &vertexBuffer);
			glBindBuffer (GL_ARRAY_BUFFER, Sphere::vertexBuffer);

			// Buffer The Vertex Data
			glBufferData (GL_ARRAY_BUFFER, vertexBufferData.size () * sizeof (glm::vec3), &vertexBufferData [0], GL_STATIC_DRAW);
			glEnableVertexAttribArray (0);
			glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

			// Gen And Bind The Index Buffer
			glGenBuffers (1, &indexBuffer);
			glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, Sphere::indexBuffer);
			glBufferData (GL_ELEMENT_ARRAY_BUFFER, indexBufferData.size () * sizeof (unsigned int), &indexBufferData [0], GL_STATIC_DRAW);

			// Unbind The VAO
			glBindVertexArray (0);

			return true;
		}

/*============================================================================================================*/

		// Draw The Sphere
		void Sphere::Draw (Camera* Camera){

			// Set The Matrix Transforms
			Sphere::material -> SetUniform ("M", Sphere::GetParentTransforms () * Sphere::mMatrix);
			Sphere::material -> SetUniform ("V", Camera -> vMatrix);
			Sphere::material -> SetUniform ("P", Camera -> pMatrix);
			Sphere::material -> SetUniform ("VP", Window::vpMatrix);

			// Set Line Colour
			Sphere::material -> SetUniform ("Colour", Sphere::colour);

			// Bind The Material
			Sphere::material -> Bind (true);

			// Bind VAO And Draw
			glBindVertexArray (Sphere::arrayBuffer);
				glDrawElements (GL_TRIANGLES, Sphere::indexBufferData.size (), GL_UNSIGNED_INT, nullptr);
			glBindVertexArray (0);

			// Unbind Material
			Sphere::material -> Bind (false);
		}

/*============================================================================================================*/
/*------DESTRUCTOR--------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Destroy The Sphere
		Sphere::~Sphere (){

			glDeleteVertexArrays (1, &arrayBuffer);
			glDeleteBuffers		 (1, &vertexBuffer);
			glDeleteBuffers		 (1, &indexBuffer);
		}
	}
}