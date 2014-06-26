#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

// Forward Declare Awesomium Classes
namespace Awesomium{

	class BitmapSurface;
	class WebCore;
	class WebSession;
	class WebView;
}

/*============================================================================================================*/

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

		// Forward Declare Rendering Classes
		class Material;
		class Texture;

/*============================================================================================================*/

		// The GUI Class
		class GUI{
		public:

			// Constructor / Destructor
			GUI ();
			virtual ~GUI ();

			// Functions
			bool Load (std::string File, Material* Material);
			bool LoadFromURL (std::string WebAddress, Material* Material);
			void SetDiscardColour (glm::vec4 DiscardColour);
			void Draw ();

			// Variables - Web
			Awesomium::BitmapSurface* bitmapSurface;
			Awesomium::WebSession* webSession;
			Awesomium::WebView* webView;

			// Variables - Materials / Textures
			Material* material;
			std::shared_ptr <Texture> texture;
			glm::vec4 discardColour;

			// Variables - Buffers
			unsigned int arrayBuffer;
			unsigned int vertexBuffer;

			// Variables - Static
			static Awesomium::WebCore* webCore;

		private:

			// Functions
			void Update ();
			void InjectUserInput ();
		};
	}
}