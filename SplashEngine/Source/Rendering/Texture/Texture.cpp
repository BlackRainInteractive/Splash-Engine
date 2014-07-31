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

			// Create A Temp TexData Object
			TexData texDataTemp;

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

				// Set The Tex Data Variables
				texDataTemp.id     = texID;
				texDataTemp.width  = texWidth;
				texDataTemp.height = texHeight;

				// Add The Texture
				Texture::textureData [TextureName] = texDataTemp;

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

			// Create A Temp TexData Object
			TexData texDataTemp;

			// Create The Texture Path Array
			std::string texPathList [6] = {PosX, NegX, PosY, NegY, PosZ, NegZ};

			// Create And Bind The Texture
			unsigned int texID = 0;

			glGenTextures (1, &texID);
			glBindTexture (GL_TEXTURE_CUBE_MAP, texID);

			// Create The Width And Height Variables
			unsigned int texWidth;
			unsigned int texHeight;

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
					texWidth  = FreeImage_GetWidth (imageBitmap);
					texHeight = FreeImage_GetHeight (imageBitmap);

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

			// Unbind Texture
			glBindTexture (GL_TEXTURE_2D, 0);

			// Set The Tex Data Variables
			texDataTemp.id     = texID;
			texDataTemp.width  = texWidth;
			texDataTemp.height = texHeight;

			// Add The Texture
			Texture::textureData [TextureName] = texDataTemp;

			return true;
		}

/*============================================================================================================*/

		// Add Texture (From Existing ID)
		void Texture::Load (unsigned int TextureID, unsigned int Width, unsigned int Height, std::string TextureName){

			// Create Temp Tex Data Object
			TexData texDataTemp;

			// Set Data Variables
			texDataTemp.id	   = TextureID;
			texDataTemp.width  = Width;
			texDataTemp.height = Height;

			// Add The Data
			Texture::textureData [TextureName] = texDataTemp;
		}

/*============================================================================================================*/

		// Get The ID Of The Selected Texture
		unsigned int Texture::GetID (std::string Texture){
			return (Texture::textureData [Texture].id);
		}

/*============================================================================================================*/

		// Check If Texture Exists
		bool Texture::Exists (std::string Texture){

			// Iterate Through Texture List
			auto it = textureData.find (Texture);

			// Return Texture Found
			if (it != textureData.end())
				return true;

			// Return Texture Not Found
			return false;
		}

/*============================================================================================================*/

		// Bind Selected Texture
		void Texture::Bind (Material* Material, std::string Texture, TEXTURE_SLOT TexSlot, int TexIndex){

			glActiveTexture (TexSlot);
			glBindTexture (GL_TEXTURE_2D, Texture::textureData [Texture].id);
			Material -> SetUniform (Texture, TexIndex);
		}

/*============================================================================================================*/

		// Bind All Textures
		void Texture::BindAll (Material* Material){

			// Create Counter
			int counter = 0;

			// Loop Though Map And Pass Texture
			for (auto tex : Texture::textureData){

				Texture::Bind (Material, tex.first.c_str (), TEXTURE_SLOT (TEXTURE_SLOT::SLOT0 + counter), counter);
				++counter;
			}
		}

/*============================================================================================================*/

		// Get The Texture Width
		int Texture::GetWidth (std::string Texture){
			return (Texture::textureData [Texture].width);
		}

/*============================================================================================================*/

		// Get The Texture Height
		int Texture::GetHeight (std::string Texture){
			return (Texture::textureData [Texture].height);
		}

/*============================================================================================================*/
/*------DESTRUCTOR--------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Destroy The Texture
		Texture::~Texture (){

			for (auto tex : Texture::textureData)
				glDeleteTextures (1, &tex.second.id);
		}
	}
}
