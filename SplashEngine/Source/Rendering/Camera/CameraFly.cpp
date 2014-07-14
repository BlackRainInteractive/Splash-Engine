//============================================================================
// Name        : CameraFly.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#define GLM_FORCE_RADIANS

#include "CameraFly.h"
#include "../../Input/Input.h"
#include "../../Time/Time.h"
#include "../../Window/Window.h"

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Setup The Camera
		void CameraFly::SetupCamera (CAMERA_MODE CameraMode, float MoveSpeed, float LookSpeed){

			// Set Camera Variables
			CameraFly::cameraMode = CameraMode;
			CameraFly::moveSpeed  = MoveSpeed;
			CameraFly::lookSpeed  = LookSpeed;
		}

/*============================================================================================================*/

		// Update The Camera
		void CameraFly::Update (){

			// Calc Projection Matrix
			switch (CameraFly::cameraMode){

			case CAMERA_MODE::ORTHO:
					CameraFly::pMatrix = glm::ortho (CameraFly::left, CameraFly::right, CameraFly::bottom, 
													 CameraFly::top, CameraFly::nearZ, CameraFly::farZ);
					break;

			case CAMERA_MODE::PERSPECTIVE:
					CameraFly::pMatrix = glm::perspective (glm::radians (CameraFly::fov), CameraFly::aspectRatio, 
														   CameraFly::nearZ, CameraFly::farZ);
					break;
			}

			// Calc Camera View
			CameraFly::UpdateView ();

			// Calc View Matrix
			if (CameraFly::parent != nullptr)
				CameraFly::vMatrix = glm::lookAt (CameraFly::position, CameraFly::target, 
												  CameraFly::upVec) * glm::inverse (CameraFly::parent -> mMatrix);

			else
				CameraFly::vMatrix = glm::lookAt (CameraFly::position, CameraFly::target, CameraFly::upVec);
		}

/*============================================================================================================*/
/*------PROTECTED FUNCTIONS-----------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Update The Camera View
		void CameraFly::UpdateView (){

			// Get Mouse Position, Then Reset It
			glm::vec2 mousePos = Input::GetMousePos ();
			Input::SetMousePos (Window::width / 2, Window::height / 2);

			// Calc Camera Rotation
			CameraFly::rotation.x += (CameraFly::lookSpeed * ((float) Window::height * 0.5f - (float) mousePos.y)) * (float) Time::deltaTime;
			CameraFly::rotation.y += (CameraFly::lookSpeed * ((float) Window::width  * 0.5f - (float) mousePos.x)) * (float) Time::deltaTime;

			// Convert Rotation From Degrees To Radians
			glm::vec3 camRot = glm::radians (CameraFly::rotation);

			// Convert Rotation To Cartesian Coordinates
			glm::vec3 direction (cosf (camRot.x) * sinf (camRot.y),
								 sinf (camRot.x),
								 cosf (camRot.x) * cosf (camRot.y));

			// Get Right Vector
			glm::vec3 right (sinf (camRot.y - 3.14f * 0.5f),
							 0,
							 cosf (camRot.y - 3.14f * 0.5f));

			// Get Up Vector
			CameraFly::upVec = glm::cross (right, direction);

			// Move Camera Forward
			if (Input::GetKeyPressed (KEY::KEY_W))
				CameraFly::position += direction * (float) Time::deltaTime * CameraFly::moveSpeed;

			// Move Camera Back
			if (Input::GetKeyPressed (KEY::KEY_S))
				CameraFly::position -= direction * (float) Time::deltaTime * CameraFly::moveSpeed;

			// Strafe Camera Right
			if (Input::GetKeyPressed (KEY::KEY_D))
				CameraFly::position += right * (float) Time::deltaTime * CameraFly::moveSpeed;

			// Strafe Camera Left
			if (Input::GetKeyPressed (KEY::KEY_A))
				CameraFly::position -= right * (float) Time::deltaTime * CameraFly::moveSpeed;

			// Move Camera Up
			if (Input::GetKeyPressed (KEY::KEY_E))
				CameraFly::position.y += CameraFly::moveSpeed * (float) Time::deltaTime;

			// Move Camera Down
			if (Input::GetKeyPressed (KEY::KEY_Q))
				CameraFly::position.y -= CameraFly::moveSpeed * (float) Time::deltaTime;

			// Set Camera Target
			CameraFly::target = (CameraFly::position + direction);
		}
	}
}
