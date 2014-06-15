#pragma once

#include "../../Base/GameObject.h"

// The Splash Engine Namespace
namespace se{

	// The Camera Type Enum
	enum CAMERA_TYPE{

		ORTHO		= 0,
		PERSPECTIVE = 1
	};

/*============================================================================================================*/

	// The Camera Mode Enum
	enum CAMERA_MODE{

		TARGET = 0,
		FPS	   = 1
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
			void SetupCamera	  (CAMERA_TYPE CameraType, CAMERA_MODE CameraMode);
			void SetupOrtho		  (float Left, float Right, float Top, float Bottom, float Near = 0.1f, float Far = 100);
			void SetupPerspective (float FOV = 65, float Near = 0.1f, float Far = 100);
			void SetupTarget	  (glm::vec3 Target);
			void SetupFPS		  (float LookSpeed, float MoveSpeed);

			// Functions - Updating
			void Update ();

			// Variables - Transform
			glm::mat4 vMatrix;
			glm::mat4 pMatrix;
			glm::vec3 upVec;
			glm::vec3 target;

			// Variables - View
			float nearZ, farZ;
			float fov, aspectRatio;
			float left, right, top, bottom;

			// Variables - FPS
			float lookSpeed, moveSpeed;

			// Variables - Misc
			CAMERA_TYPE cameraType;
			CAMERA_MODE cameraMode;

		private:

			// Functions - Updating
			void UpdateFPS ();
		};
	}
}