//============================================================================
// Name        : Display.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include <string>

// The Splash Engine Namespace
namespace se{

	// The Save Image Type Enum
	enum SCREENSHOT_FORMAT{

		BMP	   = 0,
		ICO	   = 1,
		JPEG   = 2,
		JNG	   = 3,
		PBM	   = 7,
		PBMRAW = 8,
		PGM	   = 11,
		PGMRAW = 12,
		PNG	   = 13,
		PPM	   = 14,
		PPMRAW = 15,
		TARGA  = 17,
		TIFF   = 18,
		WBMP   = 19,
		XPM	   = 23,
		GIF	   = 25,
		HDR	   = 26,
		EXR	   = 29,
		J2K	   = 30,
		JP2	   = 31,
		PFM	   = 32
	};

/*============================================================================================================*/

	// The Utility Namespace
	namespace utility{

		// The Display Class
		class Display{
		public:

			// Functions
			static void SaveScreenShot (std::string FilePath, SCREENSHOT_FORMAT Format);
			static void SetGamma (float Gamma);
			static int GetDisplayWidth ();
			static int GetDisplayHeight ();
			static int GetPixelCount (); 
		};
	}
}