//============================================================================
// Name        : GameObject.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include <glm/ext.hpp>
#include <string>

// The Splash Engine Namespace
namespace se{

	// The Base Namespace
	namespace base{

		// The GameObject Class
		class GameObject{
		public:

			// Functions
			virtual void SetParent (GameObject* Parent);
			virtual void SetLayer (std::string Tag);
			virtual void Transform (glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale = glm::vec3 (1));
			virtual void Transform (glm::mat4 ModelMatrix);
			virtual glm::mat4 GetParentTransforms ();

			// Variables - Transform
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;
			glm::mat4 mMatrix;
			std::string layer;

			// Variables - Misc
			GameObject* parent;
		};
	}
}
