//============================================================================
// Name        : GUISkin.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include <string>

// The Splash Engine Namespace
namespace se{

//============================================================================

	// The GUI Texture Type Enum
	enum GUI_TEXTURE_TYPE{

		BUTTON_NORM  = 0,
		BUTTON_HOVER = 1,
		BUTTON_PRESS = 2
	};

//============================================================================

	// The Rendering Namespace
	namespace rendering{

		// The GUI Skin Class
		class GUISkin{
		public:

			// Functions
			bool Add (std::string TexturePath, GUI_TEXTURE_TYPE TextureType);
		};
	}
}
