//============================================================================
// Name        : Camera.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include "../../Base/GameObject.h"

// The Splash Engine Namespace
namespace se{

	// The Camera Mode Enum
	enum CAMERA_MODE{

		ORTHO		= 0,
		PERSPECTIVE = 1
	};

/*============================================================================================================*/

	// The Rendering Namespace
	namespace rendering{

		// The Camera Class
		class Camera : public base::GameObject{
		public:

			// Constructor / Destructor
			Camera ();

			// Functions - Setup
			virtual void SetupCamera	  (CAMERA_MODE CameraMode);
			virtual void SetupOrtho		  (float Left, float Right, float Top, float Bottom, float Near = 0.1f, float Far = 100);
			virtual void SetupPerspective (float FOV = 65, float Near = 0.1f, float Far = 100);

			// Functions - Updating
			virtual void Update ();

			// Variables - Transform
			glm::mat4 vMatrix;
			glm::mat4 pMatrix;
			glm::vec3 upVec;
			glm::vec3 target;

			// Variables - View
			float nearZ, farZ;
			float fov, aspectRatio;
			float left, right, top, bottom;

			// Variables - Misc
			CAMERA_MODE cameraMode;

		protected:

			// Functions - Updating
			virtual void UpdateView ();
		};
	}
}