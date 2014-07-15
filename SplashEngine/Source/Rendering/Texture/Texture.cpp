//============================================================================
// Name        : Texture.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "Texture.h"
#include "../../Utility/DebugLog/DebugLog.h"
#include "../Material/Material.h"
#include <FreeImage.h>
#include <GL/glew.h>
#include <vector>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Add A Texture (From A File)
		bool Texture::Load (std::string TexturePath, std::string TextureName){

			// Get Image File Type
			FREE_IMAGE_FORMAT imageFormat = FreeImage_GetFileType (TexturePath.c_str ());
			FIBITMAP* imageBitmap;

			// If Format Not Found, Get From File Extension
			if (imageFormat == FIF_UNKNOWN)
				FreeImage_GetFIFFromFilename (TexturePath.c_str ());

			// If Still Unknown, Return Error
			if (imageFormat == FIF_UNKNOWN){

				utility::DebugLog::WriteLog ("The Texture \"" + TexturePath + "\" could not be loaded. Unknown file type", LOG_TYPE::WARNING);
				return false;
			}

			// Check If Format Is Supported
			if (FreeImage_FIFSupportsReading (imageFormat))
				imageBitmap = FreeImage_Load (imageFormat, TexturePath.c_str ());

			// If Not Return Error
			else{

				utility::DebugLog::WriteLog ("The Texture \"" + TexturePath + "\" could not be loaded. Format not supported.", LOG_TYPE::WARNING);
				return false;
			}

			// Convert Texture To 32 Bit Format
			FIBITMAP* tempBitmap = imageBitmap;
			imageBitmap = FreeImage_ConvertTo32Bits (tempBitmap);
			FreeImage_Unload (tempBitmap);

			// If Image Is Loaded, Create OpenGL Texture
			if (imageBitmap != nullptr){

				unsigned int texID = 0;

				// Generate Texture
				glGenTextures (1, &texID);
				glBindTexture (GL_TEXTURE_2D, texID);

				// Get Texture Data
				BYTE* pixels = FreeImage_GetBits (imageBitmap);

				// Get Width And Height
				unsigned int texWidth  = FreeImage_GetWidth (imageBitmap);
				unsigned int texHeight = FreeImage_GetHeight (imageBitmap);

				// Apply Data To Texture
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri (GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
				glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);

				// Unload FreeImage Texture
				FreeImage_Unload (imageBitmap);
				glBindTexture (GL_TEXTURE_2D, 0);

				// Add The Texture
				Texture::textureList [TextureName] = texID;

				return true;
			}

			// If Above Fails Return Unknown Error
			else{

				utility::DebugLog::WriteLog ("The texture \"" + TexturePath + "\" could not be loaded. Unknown error.", LOG_TYPE::WARNING);
				return false;
			}
		}

/*============================================================================================================*/

		// Add A Texture (CubeMap)
		bool Texture::Load (std::string PosX, std::string NegX, 
						    std::string PosY, std::string NegY, 
						    std::string PosZ, std::string NegZ, std::string TextureName){

			// Create The Texture Path Array
			std::string texPathList [6] = {PosX, NegX, PosY, NegY, PosZ, NegZ};

			// Create And Bind The Texture
			unsigned int textureID = 0;

			glGenTextures (1, &textureID);
			glBindTexture (GL_TEXTURE_CUBE_MAP, textureID);

			// Loop Through All Textures
			for (int i = 0; i < 6; ++i){

				// Get Image File Type
				FREE_IMAGE_FORMAT imageFormat = FreeImage_GetFileType (texPathList [i].c_str ());
				FIBITMAP* imageBitmap;

				// If Format Not Found, Get From File Extension
				if (imageFormat == FIF_UNKNOWN)
					FreeImage_GetFIFFromFilename (texPathList [i].c_str ());

				// If Still Unknown, Return Error
				if (imageFormat == FIF_UNKNOWN){

					utility::DebugLog::WriteLog ("The Texture \"" + texPathList [i] + "\" could not be loaded. Unknown file type", LOG_TYPE::WARNING);
					return false;
				}

				// Check If Format Is Supported
				if (FreeImage_FIFSupportsReading (imageFormat))
					imageBitmap = FreeImage_Load (imageFormat, texPathList [i].c_str ());

				// If Not Return Error
				else{

					utility::DebugLog::WriteLog ("The Texture \"" + texPathList [i] + "\" could not be loaded. Format not supported", LOG_TYPE::WARNING);
					return false;
				}

				// Convert Texture To 32 Bit Format
				FIBITMAP* tempBitmap = imageBitmap;
				imageBitmap = FreeImage_ConvertTo32Bits (tempBitmap);
				FreeImage_Unload (tempBitmap);

				// If Image Is Loaded, Create OpenGL Texture
				if (imageBitmap != nullptr){

					// Get Texture Data
					BYTE* pixels = FreeImage_GetBits (imageBitmap);

					// Get Width And Height
					unsigned int texWidth  = FreeImage_GetWidth (imageBitmap);
					unsigned int texHeight = FreeImage_GetHeight (imageBitmap);

					// Set Texture Parameters
					glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
					glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
					glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
					glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE);

					// Buffer Texture Data
					glTexImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, texWidth, texWidth, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);

					// Unload FreeImage Texture
					FreeImage_Unload (imageBitmap);
				}

				// If Above Fails Return Unknown Error
				else{

					utility::DebugLog::WriteLog ("The texture \"" + texPathList [i] + "\" could not be loaded. Unknown error", LOG_TYPE::WARNING);
					return false;
				}
			}

			// Unbind Texture And Add To List
			glBindTexture (GL_TEXTURE_2D, 0);
			Texture::textureList [TextureName] = textureID;

			return true;
		}

/*============================================================================================================*/

		// Add Texture (From Existing ID)
		void Texture::Load (unsigned int TextureID, std::string TextureName){
			Texture::textureList [TextureName] = TextureID;
		}

/*============================================================================================================*/

		// Get The ID Of The Selected Texture
		unsigned int Texture::GetTextureID (std::string Texture){
			return (Texture::textureList [Texture]);
		}

/*============================================================================================================*/

		// Check If Texture Exists
		bool Texture::GetTextureExists (std::string Texture){

			// Iterate Through Texture List
			std::map <std::string, unsigned int>::iterator it = textureList.find (Texture);

			// Return Texture Found
			if (it != textureList.end())
				return true;

			// Return Texture Not Found
			return false;
		}

/*============================================================================================================*/

		// Bind Selected Texture
		void Texture::BindTexture (Material* Material, std::string Texture, TEXTURE_SLOT TexSlot, int TexIndex){

			glActiveTexture (TexSlot);
			glBindTexture (GL_TEXTURE_2D, Texture::textureList [Texture]);
			Material -> SetUniform (Texture, TexIndex);
		}

/*============================================================================================================*/

		// Bind All Textures
		void Texture::BindAll (Material* Material){

			// Create Counter
			int counter = 0;

			// Loop Though Map And Pass Texture
			for (auto tex : Texture::textureList){

				Texture::BindTexture (Material, tex.first.c_str (), TEXTURE_SLOT (TEXTURE_SLOT::SLOT0 + counter), counter);
				++counter;
			}
		}

/*============================================================================================================*/
/*------DESTRUCTOR--------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Destroy The Texture
		Texture::~Texture (){

			for (auto tex : Texture::textureList)
				glDeleteTextures (1, &tex.second);
		}
	}
}
