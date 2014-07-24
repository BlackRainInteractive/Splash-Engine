//============================================================================
// Name        : Camera.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#define GLM_FORCE_RADIANS

#include "Camera.h"
#include "../../Window/Window.h"

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

/*============================================================================================================*/
/*------CONSTRUCTOR-------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// The Default Constructor
		Camera::Camera (){

			// Set Default Camera Variables
			Camera::position   = glm::vec3 (0);
			Camera::rotation   = glm::vec3 (0);
			Camera::upVec	   = glm::vec3 (0, 1, 0);
			Camera::parent     = nullptr;
			Camera::viewX	   = 0;
			Camera::viewY	   = 0;
			Camera::viewWidth  = Window::width;
			Camera::viewHeight = Window::height;
		}

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Setup The Camera
		void Camera::SetupCamera (CAMERA_MODE CameraMode){
			Camera::cameraMode = CameraMode;
		}

/*============================================================================================================*/

		// Setup An Ortho Camera
		void Camera::SetupOrtho (float Left, float Right, float Top, float Bottom, float Near, float Far){

			// Set The Camera Variables
			Camera::left   = Left;
			Camera::right  = Right;
			Camera::top	   = Top;
			Camera::bottom = Bottom;
			Camera::nearZ  = Near;
			Camera::farZ   = Far;
		}

/*============================================================================================================*/

		// Setup A Perspective Camera
		void Camera::SetupPerspective (float FOV, float Near, float Far){

			// Set The Camera Variables
			Camera::fov			= FOV;
			Camera::aspectRatio = (float) Camera::viewWidth / (float) Camera::viewHeight;
			Camera::nearZ		= Near;
			Camera::farZ		= Far;
		}

/*============================================================================================================*/

		// Set The Camera Viewport
		void Camera::SetViewPort (int X, int Y, int Width, int Height){

			Camera::viewX	    = X;
			Camera::viewY	    = Y;
			Camera::viewWidth   = Width;
			Camera::viewHeight  = Height;
			Camera::aspectRatio = (float) Camera::viewWidth / (float) Camera::viewHeight;
		}

/*============================================================================================================*/

		// Update The Camera
		void Camera::Update (){

			// Calc Projection Matrix
			switch (Camera::cameraMode){

			case CAMERA_MODE::ORTHO:
					Camera::pMatrix = glm::ortho (Camera::left, Camera::right, Camera::bottom, Camera::top, Camera::nearZ, Camera::farZ);
					break;

			case CAMERA_MODE::PERSPECTIVE:
					Camera::pMatrix = glm::perspective (glm::radians (Camera::fov), Camera::aspectRatio, Camera::nearZ, Camera::farZ);
					break;
			}

			// Calc Camera View
			Camera::UpdateView ();

			// Calc View Matrix
			if (Camera::parent != nullptr)
				Camera::vMatrix = glm::lookAt (Camera::position, Camera::target, Camera::upVec) * glm::inverse (Camera::parent -> mMatrix);

			else
				Camera::vMatrix = glm::lookAt (Camera::position, Camera::target, Camera::upVec);
		}

/*============================================================================================================*/
/*------PROTECTED FUNCTIONS-----------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Update The Camera View
		void Camera::UpdateView (){

			// Convert Rotation From Degrees To Radians
			glm::vec3 camRot = glm::radians (Camera::rotation);

			// Convert Rotation To Cartesian Coordinates
			glm::vec3 direction (cosf (camRot.x) * sinf (camRot.y),
								 sinf (camRot.x),
								 cosf (camRot.x) * cosf (camRot.y));

			// Get Right Vector
			glm::vec3 right (sinf (camRot.y - 3.14f * 0.5f),
							 0,
							 cosf (camRot.y - 3.14f * 0.5f));

			// Get Up Vector
			Camera::upVec = glm::cross (right, direction);

			// Set Camera Target
			Camera::target = (Camera::position + direction);
		}
	}
}
