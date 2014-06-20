#define GLM_FORCE_RADIANS

#include "Camera.h"
#include "../../Input/Input.h"
#include "../../Time/Time.h"
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
		}

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Setup The Camera
		void Camera::SetupCamera (CAMERA_TYPE CameraType, CAMERA_MODE CameraMode){

			Camera::cameraType = CameraType;
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
			Camera::aspectRatio = (float) Window::width / (float) Window::height;
			Camera::nearZ		= Near;
			Camera::farZ		= Far;
		}

/*============================================================================================================*/

		// Setup Target Mode
		void Camera::SetupTarget (glm::vec3 Target){
			Camera::target = Target;
		}

/*============================================================================================================*/

		// Setup FPS Mode
		void Camera::SetupFPS (float LookSpeed, float MoveSpeed){

			// Set The Camera Variables
			Camera::lookSpeed = LookSpeed;
			Camera::moveSpeed = MoveSpeed;
		}

/*============================================================================================================*/

		// Update The Camera
		void Camera::Update (){

			// Calc Projection Matrix
			switch (Camera::cameraType){

			case CAMERA_TYPE::ORTHO:
					Camera::pMatrix = glm::ortho (Camera::left, Camera::right, Camera::bottom, Camera::top, Camera::nearZ, Camera::farZ);
					break;

			case CAMERA_TYPE::PERSPECTIVE:
					Camera::pMatrix = glm::perspective (glm::radians (Camera::fov), Camera::aspectRatio, Camera::nearZ, Camera::farZ);
					break;
			}

			// Calc Camera Mode
			switch (Camera::cameraMode){

			case CAMERA_MODE::FPS:
				Camera::UpdateFPS ();
				break;
			}

			// Calc View Matrix
			if (Camera::parent != nullptr)
				Camera::vMatrix = glm::lookAt (Camera::position, Camera::target, Camera::upVec) * glm::inverse (Camera::parent -> mMatrix);

			else
				Camera::vMatrix = glm::lookAt (Camera::position, Camera::target, Camera::upVec);
		}

/*============================================================================================================*/
/*------PRIVATE FUNCTIONS-------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Update The FPS Camera
		void Camera::UpdateFPS (){

			// Get Mouse Position, Then Reset It
			glm::vec2 mousePos = Input::GetMousePos ();
			Input::SetMousePos (Window::width / 2, Window::height / 2);

			// Calc Camera Rotation
			Camera::rotation.x += (Camera::lookSpeed * float (Window::height * 0.5f - mousePos.y)) * (float) Time::deltaTime;
			Camera::rotation.y += (Camera::lookSpeed * float (Window::width  * 0.5f - mousePos.x)) * (float) Time::deltaTime;

			// Convert Rotation To Cartesian Coordinates
			glm::vec3 direction (cosf (Camera::rotation.x) * sinf (Camera::rotation.y),
								 sinf (Camera::rotation.x),
								 cosf (Camera::rotation.x) * cosf (Camera::rotation.y));

			// Get Right Vector
			glm::vec3 right (sinf (Camera::rotation.y - 3.14f * 0.5f),
							 0,
							 cosf (Camera::rotation.y - 3.14f * 0.5f));

			// Get Up Vector
			Camera::upVec = glm::cross (right, direction);

			// Move Camera Forward
			if (Input::GetKeyPressed  (KEY::KEY_W))
				Camera::position += direction * (float) Time::deltaTime * Camera::moveSpeed;

			// Move Camera Back
			if (Input::GetKeyPressed  (KEY::KEY_S))
				Camera::position -= direction * (float) Time::deltaTime * Camera::moveSpeed;

			// Strafe Camera Right
			if (Input::GetKeyPressed  (KEY::KEY_D))
				Camera::position += right * (float) Time::deltaTime * Camera::moveSpeed;

			// Strafe Camera Left
			if (Input::GetKeyPressed  (KEY::KEY_A))
				Camera::position -= right * (float) Time::deltaTime * Camera::moveSpeed;

			// Move Camera Up
			if (Input::GetKeyPressed (KEY::KEY_E))
				Camera::position.y += Camera::moveSpeed * (float) Time::deltaTime;

			// Move Camera Down
			if (Input::GetKeyPressed (KEY::KEY_Q))
				Camera::position.y -= Camera::moveSpeed * (float) Time::deltaTime;

			// Set Camera Target
			Camera::target = (Camera::position + direction);
		}
	}
}