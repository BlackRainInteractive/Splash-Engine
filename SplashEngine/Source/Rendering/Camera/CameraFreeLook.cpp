//============================================================================
// Name        : CameraFreeLook.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#define GLM_FORCE_RADIANS

#include "CameraFreeLook.h"
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
		void CameraFreeLook::SetupCamera (CAMERA_MODE CameraMode, float MoveSpeed, float LookSpeed){

			// Set Camera Variables
			CameraFreeLook::cameraMode = CameraMode;
			CameraFreeLook::moveSpeed  = MoveSpeed;
			CameraFreeLook::lookSpeed  = LookSpeed;
		}

/*============================================================================================================*/

		// Update The Camera
		void CameraFreeLook::Update (){

			// Calc Projection Matrix
			switch (CameraFreeLook::cameraMode){

			case CAMERA_MODE::ORTHO:
					CameraFreeLook::pMatrix = glm::ortho (CameraFreeLook::left, CameraFreeLook::right, CameraFreeLook::bottom, 
													      CameraFreeLook::top, CameraFreeLook::nearZ, CameraFreeLook::farZ);
					break;

			case CAMERA_MODE::PERSPECTIVE:
					CameraFreeLook::pMatrix = glm::perspective (glm::radians (CameraFreeLook::fov), CameraFreeLook::aspectRatio, 
																CameraFreeLook::nearZ, CameraFreeLook::farZ);
					break;
			}

			// Calc Camera View
			CameraFreeLook::UpdateView ();

			// Calc View Matrix
			if (CameraFreeLook::parent != nullptr)
				CameraFreeLook::vMatrix = glm::lookAt (CameraFreeLook::position, CameraFreeLook::target, 
													   CameraFreeLook::upVec) * glm::inverse (CameraFreeLook::parent -> mMatrix);

			else
				CameraFreeLook::vMatrix = glm::lookAt (CameraFreeLook::position, CameraFreeLook::target, CameraFreeLook::upVec);
		}

/*============================================================================================================*/
/*------PROTECTED FUNCTIONS-----------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Update The Camera View
		void CameraFreeLook::UpdateView (){

			// Get Mouse Position, Then Reset It
			glm::vec2 mousePos = Input::GetMousePos ();
			Input::SetMousePos (Window::width / 2, Window::height / 2);

			// Calc Camera Rotation
			CameraFreeLook::rotation.x += (CameraFreeLook::lookSpeed * float (Window::height * 0.5f - mousePos.y)) * (float) Time::deltaTime;
			CameraFreeLook::rotation.y += (CameraFreeLook::lookSpeed * float (Window::width  * 0.5f - mousePos.x)) * (float) Time::deltaTime;

			// Convert Rotation From Degrees To Radians
			glm::vec3 camRot = glm::radians (CameraFreeLook::rotation);

			// Convert Rotation To Cartesian Coordinates
			glm::vec3 direction (cosf (camRot.x) * sinf (camRot.y),
								 sinf (camRot.x),
								 cosf (camRot.x) * cosf (camRot.y));

			// Get Right Vector
			glm::vec3 right (sinf (camRot.y - 3.14f * 0.5f),
							 0,
							 cosf (camRot.y - 3.14f * 0.5f));

			// Get Up Vector
			CameraFreeLook::upVec = glm::cross (right, direction);

			// Move Camera Forward
			if (Input::GetKeyPressed (KEY::KEY_W))
				CameraFreeLook::position += direction * (float) Time::deltaTime * CameraFreeLook::moveSpeed;

			// Move Camera Back
			if (Input::GetKeyPressed (KEY::KEY_S))
				CameraFreeLook::position -= direction * (float) Time::deltaTime * CameraFreeLook::moveSpeed;

			// Strafe Camera Right
			if (Input::GetKeyPressed (KEY::KEY_D))
				CameraFreeLook::position += right * (float) Time::deltaTime * CameraFreeLook::moveSpeed;

			// Strafe Camera Left
			if (Input::GetKeyPressed (KEY::KEY_A))
				CameraFreeLook::position -= right * (float) Time::deltaTime * CameraFreeLook::moveSpeed;

			// Move Camera Up
			if (Input::GetKeyPressed (KEY::KEY_E))
				CameraFreeLook::position.y += CameraFreeLook::moveSpeed * (float) Time::deltaTime;

			// Move Camera Down
			if (Input::GetKeyPressed (KEY::KEY_Q))
				CameraFreeLook::position.y -= CameraFreeLook::moveSpeed * (float) Time::deltaTime;

			// Set Camera Target
			CameraFreeLook::target = (CameraFreeLook::position + direction);
		}
	}
}