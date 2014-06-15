#define GLM_FORCE_RADIANS

#include "GameObject.h"

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
	}
}