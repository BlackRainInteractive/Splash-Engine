//============================================================================
// Name        : Texture.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include <map>
#include <string>

// The Splash Engine Namespace
namespace se{

	// The Texture Slot Enum
	enum TEXTURE_SLOT{

		SLOT0  = 0x84C0,
		SLOT1  = 0x84C1,
		SLOT2  = 0x84C2,
		SLOT3  = 0x84C3,
		SLOT4  = 0x84C4,
		SLOT5  = 0x84C5,
		SLOT6  = 0x84C6,
		SLOT7  = 0x84C7,
		SLOT8  = 0x84C8,
		SLOT9  = 0x84C9,
		SLOT10 = 0x84CA,
		SLOT11 = 0x84CB,
		SLOT12 = 0x84CC,
		SLOT13 = 0x84CD,
		SLOT14 = 0x84CE,
		SLOT15 = 0x84CF,
		SLOT16 = 0x84D0,
		SLOT17 = 0x84D1,
		SLOT18 = 0x84D2,
		SLOT19 = 0x84D3,
		SLOT20 = 0x84D4,
		SLOT21 = 0x84D5,
		SLOT22 = 0x84D6,
		SLOT23 = 0x84D7,
		SLOT24 = 0x84D8,
		SLOT25 = 0x84D9,
		SLOT26 = 0x84DA,
		SLOT27 = 0x84DB,
		SLOT28 = 0x84DC,
		SLOT29 = 0x84DD,
		SLOT30 = 0x84DE,
		SLOT31 = 0x84DF
	};

/*============================================================================================================*/

	// The Rendering Namespace
	namespace rendering{

		// Forward Declare Material Class
		class Material;

/*============================================================================================================*/

		// The Texture Data Struct
		struct TexData{

			unsigned int id;
			unsigned int width;
			unsigned int height;
		};

/*============================================================================================================*/

		// The Texture Class
		class Texture{
		public:

			// Constructor / Destructor
			virtual ~Texture ();

			// Functions - Adding Textures
			bool Load (std::string TexturePath, std::string TextureName);
			bool Load (std::string PosX, std::string NegX, 
					   std::string PosY, std::string NegY, 
					   std::string PosZ, std::string NegZ, 
					   std::string TextureName);
			void Load (unsigned int TextureID, unsigned int Width, unsigned int Height, std::string TextureName);

			// Functions - Texture Uniforms
			unsigned int GetID (std::string Texture);
			bool Exists		   (std::string Texture);
			void Bind		   (Material* Material, std::string Texture, TEXTURE_SLOT TexSlot, int TexIndex);
			void BindAll	   (Material* Material);

			// Functions - Utility
			int GetWidth  (std::string Texture);
			int GetHeight (std::string Texture);

			// Variables
			std::map <std::string, TexData> textureData;
		};
	}
}
