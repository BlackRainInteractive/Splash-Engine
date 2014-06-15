#include "Display.h"
#include "../../Window/Window.h"
#include <FreeImage.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// The Splash Engine Namespace
namespace se{

	// The Utility Namespace
	namespace utility{

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Save A Screen Shot
		void Display::SaveScreenShot (std::string FilePath, SCREENSHOT_FORMAT Format){

			// Create Pixel Array
			GLubyte* pixels = new GLubyte [3 * Window::width * Window::height];

			// Read Pixels From Screen And Buffer Into Array
			glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
			glReadPixels (0, 0, Window::width, Window::height, GL_BGR, GL_UNSIGNED_BYTE, pixels);

			// Convert To FreeImage And Save
			FIBITMAP* image = FreeImage_ConvertFromRawBits (pixels, Window::width,
															Window::height, 3 * Window::width, 24,
															0x0000FF, 0xFF0000, 0x00FF00, false);

			FreeImage_Save ((FREE_IMAGE_FORMAT) Format, image, FilePath.c_str (), 0);

			// Free Resources
			FreeImage_Unload (image);
			delete [] (pixels);
		}

/*============================================================================================================*/

		// Set The Display Gamma
		void Display::SetGamma (float Gamma){
			glfwSetGamma (glfwGetPrimaryMonitor (), Gamma);
		}

/*============================================================================================================*/

		// Get The Display Width In Pixels
		int Display::GetDisplayWidth (){

			const GLFWvidmode* mode = glfwGetVideoMode (glfwGetPrimaryMonitor ());
			return (mode -> width);
		}

/*============================================================================================================*/

		// Get The Display Height In Pixels
		int Display::GetDisplayHeight (){

			const GLFWvidmode* mode = glfwGetVideoMode (glfwGetPrimaryMonitor ());
			return (mode -> height);
		}

/*============================================================================================================*/

		// Get The Number Of Pixels
		int Display::GetPixelCount (){

			const GLFWvidmode* mode = glfwGetVideoMode (glfwGetPrimaryMonitor ());
			return (mode -> width * mode -> height);
		}
	}
}
