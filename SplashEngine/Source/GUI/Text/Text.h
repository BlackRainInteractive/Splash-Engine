#pragma once

#include "../../Base/GameObject.h"

// Forward Declare FreeType Structs
struct FT_LibraryRec_;
struct FT_FaceRec_;
struct FT_GlyphSlotRec_;

typedef struct FT_FaceRec_* FT_Face;
typedef struct FT_GlyphSlotRec_* FT_GlyphSlot;
typedef struct FT_LibraryRec_* FT_Library;

/*============================================================================================================*/

// The Splash Engine Namespace
namespace se{

	// Forward Declare Material Class
	namespace rendering{
		class Material;
	}

/*============================================================================================================*/

	// The GUI Namespace
	namespace gui{

		// The Text Class
		class Text : public base::GameObject{
		public:


		};
	}
}