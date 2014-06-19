#include "Grid.h"
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

		// Create The Grid
		bool Grid::Create (glm::vec3 Position, int GridCount, glm::vec3 Colour, Material* Material){

			// Set The Grid Functions
			Grid::position = Position;
			Grid::rotation = glm::vec3 (0);
			Grid::scale	   = glm::vec3 (1);
			Grid::colour   = Colour;
			Grid::material = Material;

			// Set The Grid Model Matrix
			Grid::Transform (Grid::position, Grid::rotation);

			// Loop Though And Add Lines
			for (int i = 0 ; i < GridCount + 1; ++i){

				// X Axis
				Grid::vertexList.push_back (glm::vec3 (-(GridCount / 2) + i, 0,  (GridCount / 2)));
				Grid::vertexList.push_back (glm::vec3 (-(GridCount / 2) + i, 0, -(GridCount / 2)));

				// Y Axis
				Grid::vertexList.push_back (glm::vec3 ( GridCount / 2, 0, -(GridCount / 2) + i));
				Grid::vertexList.push_back (glm::vec3 (-GridCount / 2, 0, -(GridCount / 2) + i));
			}

			// Create And Bind The VAO
			glGenVertexArrays (1, &arrayBuffer);
			glBindVertexArray (Grid::arrayBuffer);

			// Gen And Bind The Vertex Buffer
			glGenBuffers (1, &vertexBuffer);
			glBindBuffer (GL_ARRAY_BUFFER, Grid::vertexBuffer);

			// Buffer The Vertex Data
			glBufferData (GL_ARRAY_BUFFER, Grid::vertexList.size () * sizeof (glm::vec3), &Grid::vertexList [0], GL_STATIC_DRAW);
			glEnableVertexAttribArray (0);
			glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

			// Unbind The VAO
			glBindVertexArray (0);

			return true;
		}

/*============================================================================================================*/

		// Draw The Grid
		void Grid::Draw (Camera* Camera){

			// Set The Matrix Transforms
			Grid::material -> SetUniform ("M", Grid::mMatrix);
			Grid::material -> SetUniform ("V", Camera -> vMatrix);
			Grid::material -> SetUniform ("P", Camera -> pMatrix);

			// Set Line Colour
			Grid::material -> SetUniform ("Colour", Grid::colour);

			// Bind The Material
			Grid::material -> Bind (true);

			// Bind VAO And Draw
			glBindVertexArray (Grid::arrayBuffer);
			glDrawArrays (GL_LINES, 0, Grid::vertexList.size ());
			glBindVertexArray (0);

			// Unbind Material
			Grid::material -> Bind (false);
		}

/*============================================================================================================*/
/*------DESTRUCTOR--------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Destroy The Line
		Grid::~Grid (){

			glDeleteVertexArrays (1, &arrayBuffer);
			glDeleteBuffers		 (1, &vertexBuffer);
		}
	}
}