#include "Input.h"
#include <iostream>
#include <GLFW/glfw3.h>

// The Splash Engine Namespace
namespace se{

	// Init Static Variables
	std::map <int, INPUT_STATE> Input::keyStateList;
	std::map <int, INPUT_STATE> Input::mouseStateList;
	glm::vec2 Input::mousePos;

/*============================================================================================================*/
/*------CONSTRUCTOR-------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

	// Set Up The Input Class
	Input::Input (){

		// Set All Key States To Release
		for (int i = 32; i < KEY::KEY_LAST; ++i)
			Input::keyStateList [i] = INPUT_STATE::RELEASED;

		// Set All Mouse States To Release
		for (int i = 0; i < 3; ++i)
			Input::mouseStateList [i] = INPUT_STATE::RELEASED;

		// Set The CallBacks
		glfwSetKeyCallback         (glfwGetCurrentContext (), Input::KeyCallbackFunc);
		glfwSetMouseButtonCallback (glfwGetCurrentContext (), Input::MouseButtonCallbackFunc);
		glfwSetCursorPosCallback   (glfwGetCurrentContext (), Input::MousePosCallbackFunc);
	}

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

	// Get Keyboard Key Pressed
	bool Input::GetKey (KEY Key, INPUT_STATE KeyState){

		// Check For Pressed And Held
		if (KeyState == INPUT_STATE::PRESSED_OR_HELD){

			// Check If Key Is Pressed
			if (Input::keyStateList [Key] == INPUT_STATE::PRESSED || Input::keyStateList [Key] == INPUT_STATE::REPEAT)
				return true;

			else
				return false;
		}

		else{

			// Check If Key Is Pressed
			if (Input::keyStateList [Key] == KeyState)
				return true;

			else
				return false;
		}
	}

/*============================================================================================================*/

	// Get The Mouse Button Pressed
	bool Input::GetMousePressed (MOUSE_BUTTON Mouse, INPUT_STATE KeyState){

		// Check If Key Is Pressed
		if (Input::mouseStateList [Mouse] == KeyState)
			return true;

		else
			return false;
	}

/*============================================================================================================*/

	// Get The Mouse Position
	glm::vec2 Input::GetMousePos (){
		return (Input::mousePos);
	}

/*============================================================================================================*/

	// Set The Mouse Position
	void Input::SetMousePos (int X, int Y){

		glfwSetCursorPos (glfwGetCurrentContext (), X, Y);
		Input::mousePos = glm::vec2 (X, Y);
	}

/*============================================================================================================*/
/*------PRIVATE FUNCTIONS-------------------------------------------------------------------------------------*/
/*============================================================================================================*/

	// The Key Callback Function
	void Input::KeyCallbackFunc (GLFWwindow* Window, int Key, int ScanCode, int Action, int Mods){

		// Set The Key State
		Input::keyStateList [Key] = (INPUT_STATE) Action;
	}

/*============================================================================================================*/

	// The Mouse Button Callback Function
	void Input::MouseButtonCallbackFunc (GLFWwindow* Window, int Key, int Action, int Mods){

		// Set The Mouse State
		Input::mouseStateList [Key] = (INPUT_STATE) Action;
	}

/*============================================================================================================*/

	// The Mouse Position Callback
	void Input::MousePosCallbackFunc (GLFWwindow* Window, double XPos, double YPos){
		Input::mousePos = glm::vec2 ((int) XPos, (int) YPos);
	}
}
