//============================================================================
// Name        : Line.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "Line.h"
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

		// Create The Line
		bool Line::Create (glm::vec3 StartPos, glm::vec3 EndPos, glm::vec3 Colour, Material* Material){

			// Set The Line Variables
			Line::startPos = StartPos;
			Line::endPos   = EndPos;
			Line::colour   = Colour;
			Line::material = Material;

			// Create The Vertex Buffer Data
			const float vertexBufferData [] = {Line::startPos.x, Line::startPos.y, Line::startPos.z,
											   Line::endPos.x  , Line::endPos.y  , Line::endPos.z};

			// Create And Bind The VAO
			glGenVertexArrays (1, &arrayBuffer);
			glBindVertexArray (Line::arrayBuffer);

			// Gen And Bind The Vertex Buffer
			glGenBuffers (1, &vertexBuffer);
			glBindBuffer (GL_ARRAY_BUFFER, Line::vertexBuffer);

			// Buffer The Vertex Data
			glBufferData (GL_ARRAY_BUFFER, sizeof (vertexBufferData), &vertexBufferData, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray (0);
			glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

			// Unbind The VAO
			glBindVertexArray (0);

			return true;
		}

/*============================================================================================================*/

		// Transform The Line Verts
		void Line::Transform (glm::vec3 StartPos, glm::vec3 EndPos){

			// Set The Line Variables
			Line::startPos = StartPos;
			Line::endPos   = EndPos;

			// Create The Vertex Buffer Data
			const float vertexBufferData [] = {Line::startPos.x, Line::startPos.y, Line::startPos.z,
											   Line::endPos.x  , Line::endPos.y  , Line::endPos.z};

			// Bind The VBO, And Buffer The Data
			glBindBuffer    (GL_ARRAY_BUFFER, Line::vertexBuffer);
			glBufferSubData (GL_ARRAY_BUFFER, 0, sizeof (vertexBufferData), &vertexBufferData);
			glBindBuffer    (GL_ARRAY_BUFFER, 0);
		}

/*============================================================================================================*/

		// Draw The Line
		void Line::Draw (Camera* Camera){

			// Set The Matrix Transforms
			Line::material -> SetUniform ("M", glm::mat4 (1));
			Line::material -> SetUniform ("V", Camera -> vMatrix);
			Line::material -> SetUniform ("P", Camera -> pMatrix);

			// Set Line Colour
			Line::material -> SetUniform ("Colour", Line::colour);

			// Bind The Material
			Line::material -> Bind (true);

			// Bind VAO And Draw
			glBindVertexArray (Line::arrayBuffer);
			glDrawArrays (GL_LINES, 0, 2);
			glBindVertexArray (0);

			// Unbind Material
			Line::material -> Bind (false);
		}

/*============================================================================================================*/
/*------DESTRUCTOR--------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Destroy The Line
		Line::~Line (){

			glDeleteVertexArrays (1, &arrayBuffer);
			glDeleteBuffers		 (1, &vertexBuffer);
		}
	}
}
