#pragma once

#include <glm/ext.hpp>

// The Splash Engine Namespace
namespace se{

	// The Base Namespace
	namespace base{

		// The GameObject Class
		class GameObject{
		public:

			// Functions
			virtual void SetParent (GameObject* Parent);
			virtual void Transform (glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale = glm::vec3 (1));
			virtual void Transform (glm::mat4 ModelMatrix);

			// Variables - Transform
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;
			glm::mat4 mMatrix;

			// Variables - Misc
			GameObject* parent;
		};
	}
}
