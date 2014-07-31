//============================================================================
// Name        : GameObject.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#define GLM_FORCE_RADIANS

#include "GameObject.h"
#include <vector>

// The Splash Engine Namespace
namespace se{

	// The Base Namespace
	namespace base{

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Set The GameObjects Parent
		void GameObject::SetParent (GameObject* Parent){
			GameObject::parent = Parent;
		}

/*============================================================================================================*/

		// Set The GameObjects Layer
		void GameObject::SetLayer (std::string Tag){
			GameObject::layer = Tag;
		}

/*============================================================================================================*/

		// Transform The GameObject (Via Vectors)
		void GameObject::Transform (glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale){

			// Set The GameObject Variables
			GameObject::position = Position;
			GameObject::rotation = Rotation;
			GameObject::scale	 = Scale;

			// Create The Model Matrix
			GameObject::mMatrix = glm::translate (glm::mat4 (1.0f), Position);
			GameObject::mMatrix = glm::rotate    (GameObject::mMatrix, glm::radians (Rotation.x), glm::vec3 (1, 0, 0));
			GameObject::mMatrix = glm::rotate    (GameObject::mMatrix, glm::radians (Rotation.y), glm::vec3 (0, 1, 0));
			GameObject::mMatrix = glm::rotate    (GameObject::mMatrix, glm::radians (Rotation.z), glm::vec3 (0, 0, 1));
			GameObject::mMatrix = glm::scale     (GameObject::mMatrix, Scale);
		}

/*============================================================================================================*/

		// Transform The GameObject (Via Model Matrix)
		void GameObject::Transform (glm::mat4 ModelMatrix){
			GameObject::mMatrix = ModelMatrix;
		}

/*============================================================================================================*/
/*------PROTECTED FUNCTIONS-----------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Get Parent Transforms
		glm::mat4 GameObject::GetParentTransforms (){

			// Check If Object Has A Parent
			if (GameObject::parent == nullptr)
				return (glm::mat4 (1));

			// Create Required Variables
			std::vector <glm::mat4> matrixList;
			GameObject* currentObject = GameObject::parent;
			glm::mat4 returnMatrix;

			// Find All Parents
			while (true){

				// Check If Parent Exists
				if (currentObject != nullptr){

					// Add Matrix To List
					matrixList.push_back (currentObject -> mMatrix);

					// Move To Next Parent
					currentObject = currentObject -> parent;
				}

				// Exit Loop
				else
					break;
			}

			// Set Return Matrix
			returnMatrix = matrixList [matrixList.size () - 1];

			// Remove Last Element And Reverse Order
			matrixList.pop_back ();
			std::reverse (matrixList.begin (), matrixList.end ());

			// Loop Through List, And Add To Final Matrix
			for (auto m : matrixList)
				returnMatrix *= m;

			// Return The Matrix
			return (returnMatrix);
		}
	}
}
