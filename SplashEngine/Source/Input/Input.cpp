#include "Input.h"
#include <GLFW/glfw3.h>

// The Splash Engine Namespace
namespace se{

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

	// Get Keyboard Key Pressed
	bool Input::GetKeyPressed (KEY Key){

		// Check If Key Is Pressed
		if (glfwGetKey (glfwGetCurrentContext (), Key))
			return true;

		else
			return false;
	}

/*============================================================================================================*/

	// Get The Mouse Button Pressed
	bool Input::GetMousePressed (MOUSE_BUTTON Mouse){

		// Check If Key Is Pressed
		if (glfwGetMouseButton (glfwGetCurrentContext (), Mouse))
			return true;

		else
			return false;
	}

/*============================================================================================================*/

	// Get The Mouse Position
	glm::vec2 Input::GetMousePos (){

		// Get The Mouse Position
		double x, y;
		glfwGetCursorPos (glfwGetCurrentContext (), &x, &y);

		// Return Value
		return (glm::vec2 (x, y));
	}

/*============================================================================================================*/

	// Set The Mouse Position
	void Input::SetMousePos (int X, int Y){
		glfwSetCursorPos (glfwGetCurrentContext (), X, Y);
	}
}