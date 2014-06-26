#include "GUI.h"
#include "../../Input/Input.h"
#include "../../Window/Window.h"
#include "../Material/Material.h"
#include "../Texture/Texture.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/WebSession.h>
#include <Awesomium/WebPreferences.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>
#include <GL/glew.h>
#include <iostream>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

		// Forward Declare Static Classes
		Awesomium::WebCore* GUI::webCore;

/*============================================================================================================*/
/*------CONSTRUCTOR-------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// The Default GUI Constructor
		GUI::GUI (){

			// Set Up The Web Prefrences
			Awesomium::WebPreferences webPref = Awesomium::WebPreferences ();
			webPref.enable_gpu_acceleration = true;
			webPref.enable_smooth_scrolling = true;
			webPref.enable_web_gl			= true;
			webPref.enable_dart				= true;
			webPref.enable_javascript		= true;
			webPref.enable_plugins			= true;

			// Create The Web Session And View
			GUI::webSession = GUI::webCore -> CreateWebSession (Awesomium::WebString::CreateFromUTF8 ("", strlen ("")), webPref);
			GUI::webView    = GUI::webCore -> CreateWebView (Window::width, Window::height, GUI::webSession, Awesomium::kWebViewType_Offscreen);

			// Create A New Texture
			GUI::texture = std::shared_ptr <Texture> (new Texture);

			// Create The Quad Vert Data
			const float vertexBufferData [] = {-1, -1, 0,
												1, -1, 0,
											   -1,  1, 0,
												1,  1, 0};

			// Create And Bind The VAO
			glGenVertexArrays (1, &arrayBuffer);
			glBindVertexArray (GUI::arrayBuffer);

			// Gen And Bind The Vertex Buffer
			glGenBuffers (1, &vertexBuffer);
			glBindBuffer (GL_ARRAY_BUFFER, GUI::vertexBuffer);

			// Buffer The Vertex Data
			glBufferData (GL_ARRAY_BUFFER, sizeof (vertexBufferData), &vertexBufferData, GL_STATIC_DRAW);
			glEnableVertexAttribArray (0);
			glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

			// Unbind The VAO
			glBindVertexArray (0);

			// Create Texture ID
			unsigned int diffuseTexture;

			// Create Textures
			glGenTextures (1, &diffuseTexture);

			// Configure Diffuse Texture
			glBindTexture	(GL_TEXTURE_2D, diffuseTexture);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D	(GL_TEXTURE_2D, 0, GL_RGBA, Window::width, Window::height, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);

			// Add Textures To Texture Class
			GUI::texture -> Load (diffuseTexture, "diffuseTexture");
		}

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Load The GUI From A URL
		bool GUI::LoadFromURL (std::string WebAddress, Material* Material){

			// Set The GUI Properties
			GUI::material = Material;

			// Load The Web Address
			Awesomium::WebURL url (Awesomium::WSLit (WebAddress.c_str ()));

			// Check If URL Is Valid
			if (!url.IsValid ()){

				// Print Error
				std::cout << "ERROR: The URL '" << WebAddress << "' is invalid.\n";
				return false;
			}

			// Set The Address
			GUI::webView -> LoadURL (url);

			// Wait For Page To Load
			while (GUI::webView -> IsLoading ())
				GUI::webCore -> Update ();

			// Return True
			return true;
		}

/*============================================================================================================*/

		// Set The Discard Colour
		void GUI::SetDiscardColour (glm::vec4 DiscardColour){
			GUI::discardColour = DiscardColour;
		}

/*============================================================================================================*/

		// Draw The GUI
		void GUI::Draw (){

			// Update The GUI
			GUI::Update ();

			// Set Window Size
			GUI::material -> SetUniform ("WindowSize", glm::vec2 (Window::width, Window::height));

			// Set The Discard Colour
			GUI::material -> SetUniform ("discardColour", GUI::discardColour);

			// Bind The Material
			GUI::material -> Bind (true);

			// Set Textures
			GUI::texture -> BindAll (GUI::material);

			// Bind VAO And Draw Fullscreen Quad
			glBindVertexArray (GUI::arrayBuffer);
			glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray (0);

			// Unbind The Material
			GUI::material -> Bind (false);
		}

/*============================================================================================================*/
/*------PRIVATE FUNCTIONS-------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Update The GUI
		void GUI::Update (){

			// Inject User Input
			GUI::InjectUserInput ();

			// Get The Web Surface And Buffer
			GUI::bitmapSurface = (Awesomium::BitmapSurface*) GUI::webView -> surface ();
			unsigned char* buffer = new unsigned char [Window::width * Window::height * 4];

			// Update The Texture Buffer
			GUI::bitmapSurface -> CopyTo (buffer, Window::width * 4, 4, false, true);

			// Buffer The Texture Data
			glBindTexture   (GL_TEXTURE_2D, GUI::texture.get () -> GetTextureID ("diffuseTexture"));
			glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, Window::width, Window::height, GL_BGRA, GL_UNSIGNED_BYTE, buffer);
			glBindTexture   (GL_TEXTURE_2D, 0);

			// Delete The Buffer
			delete[] buffer;
		}

/*============================================================================================================*/

		// Inject User Input Into HTML Page
		void GUI::InjectUserInput (){

			// Send Mouse Position
			GUI::webView -> InjectMouseMove ((int) Input::GetMousePos ().x, (int) Input::GetMousePos ().y);

			// Send Mouse Button Left
			if (Input::GetMouse (MOUSE_BUTTON::LEFT, INPUT_STATE::PRESSED))
				GUI::webView -> InjectMouseDown (Awesomium::MouseButton::kMouseButton_Left);

			else
				GUI::webView -> InjectMouseUp (Awesomium::MouseButton::kMouseButton_Left);
		}

/*============================================================================================================*/
/*------DESTRUCTOR--------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Destroy The GUI
		GUI::~GUI (){

			// Destroy Buffers
			glDeleteVertexArrays (1, &arrayBuffer);
			glDeleteBuffers		 (1, &vertexBuffer);

			// Close Web View
			GUI::webView    -> Destroy ();
			GUI::webSession -> Release ();
		}
	}
}