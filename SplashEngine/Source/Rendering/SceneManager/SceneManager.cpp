//============================================================================
// Name        : SceneManager.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "SceneManager.h"
#include "../../Base/Renderable.h"
#include "../../Optimization/BatchGroup/BatchGroup.h"
#include "../../Utility/DebugLog/DebugLog.h"
#include "../../Window/Window.h"
#include "../Camera/Camera.h"
#include "../Material/Material.h"
#include "../Skybox/Skybox.h"
#include "../Texture/Texture.h"
#include <GL/glew.h>
#include <vector>

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

/*============================================================================================================*/
/*------CONSTRUCTOR-------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// The SceneManager Defualt Constructor
		SceneManager::SceneManager (){

			// Create A New Texture
			SceneManager::textureGBuffer = std::shared_ptr <Texture> (new Texture);

			// Create The Quad Vert Data
			const float vertexBufferData [] = {-1, -1, 0,
												1, -1, 0,
											   -1,  1, 0,
												1,  1, 0};

			// Create And Bind The VAO
			glGenVertexArrays (1, &arrayGBuffer);
			glBindVertexArray (SceneManager::arrayGBuffer);

			// Gen And Bind The Vertex Buffer
			glGenBuffers (1, &vertexGBuffer);
			glBindBuffer (GL_ARRAY_BUFFER, SceneManager::vertexGBuffer);

			// Buffer The Vertex Data
			glBufferData (GL_ARRAY_BUFFER, sizeof (vertexBufferData), &vertexBufferData, GL_STATIC_DRAW);
			glEnableVertexAttribArray (0);
			glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

			// Unbind The VAO
			glBindVertexArray (0);

			// Create And Bind The FBO
			glGenFramebuffers (1, &frameGBuffer);
			glBindFramebuffer (GL_DRAW_FRAMEBUFFER, SceneManager::frameGBuffer);

			// Create Texture IDs
			unsigned int diffuseTexture;
			unsigned int specularTexture;
			unsigned int normalTexture;
			unsigned int positionTexture;
			unsigned int depthTexture;

			// Create Textures
			glGenTextures (1, &diffuseTexture);
			glGenTextures (1, &specularTexture);
			glGenTextures (1, &normalTexture);
			glGenTextures (1, &positionTexture);
			glGenTextures (1, &depthTexture);

			// Configure Diffuse Texture
			glBindTexture		 (GL_TEXTURE_2D, diffuseTexture);
			glTexParameteri		 (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri		 (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D		 (GL_TEXTURE_2D, 0, GL_RGB, Window::width, Window::height, 0, GL_RGB, GL_FLOAT, 0);
			glFramebufferTexture (GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, diffuseTexture, 0);

			// Configure Specular Texture
			glBindTexture		 (GL_TEXTURE_2D, specularTexture);
			glTexParameteri		 (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri		 (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D		 (GL_TEXTURE_2D, 0, GL_RGB, Window::width, Window::height, 0, GL_RGB, GL_FLOAT, 0);
			glFramebufferTexture (GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, specularTexture, 0);

			// Configure Normal Texture
			glBindTexture		 (GL_TEXTURE_2D, normalTexture);
			glTexParameteri		 (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri		 (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D		 (GL_TEXTURE_2D, 0, GL_RGB, Window::width, Window::height, 0, GL_RGB, GL_FLOAT, 0);
			glFramebufferTexture (GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, normalTexture, 0);

			// Configure Position Texture
			glBindTexture		 (GL_TEXTURE_2D, positionTexture);
			glTexParameteri		 (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri		 (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D		 (GL_TEXTURE_2D, 0, GL_RGB, Window::width, Window::height, 0, GL_RGB, GL_FLOAT, 0);
			glFramebufferTexture (GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, positionTexture, 0);

			// Configure Depth Texture
			glBindTexture		 (GL_TEXTURE_2D, depthTexture);
			glTexParameteri		 (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri		 (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D		 (GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, Window::width, Window::height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
			glFramebufferTexture (GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

			// Setup Draw Buffers
			unsigned int drawBuffers [] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
			glDrawBuffers (4, drawBuffers);

			// Check If Buffer Was Created
			GLenum status = glCheckFramebufferStatus (GL_DRAW_FRAMEBUFFER);

			if (status != GL_FRAMEBUFFER_COMPLETE)
				utility::DebugLog::WriteLog ("The GBuffer could not be created", LOG_TYPE::ERROR);

			// Add Textures To Texture Class
			SceneManager::textureGBuffer -> Load (diffuseTexture, "DiffuseBufferTexture");
			SceneManager::textureGBuffer -> Load (specularTexture, "SpecularBufferTexture");
			SceneManager::textureGBuffer -> Load (normalTexture, "NormalBufferTexture");
			SceneManager::textureGBuffer -> Load (positionTexture, "PositionBufferTexture");
			SceneManager::textureGBuffer -> Load (depthTexture, "DepthBufferTexture");

			// Bind Default FBO
			glBindFramebuffer (GL_DRAW_FRAMEBUFFER, 0);
		}

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Add Renderable
		void SceneManager::Add (base::Renderable* Object){
			SceneManager::renderableList.push_back (Object);
		}

/*============================================================================================================*/

		// Add Batch Group
		void SceneManager::Add (optimization::BatchGroup* Object){
			SceneManager::batchGroupList.push_back (Object);
		}

/*============================================================================================================*/

		// Add Skybox
		void SceneManager::Add (Skybox* Object){
			SceneManager::skyboxList.push_back (Object);
		}

/*============================================================================================================*/

		// Remove Renderable
		void SceneManager::Remove (base::Renderable* Object){

			// Loop Through Elements
			for (auto iter = SceneManager::renderableList.begin (); iter != SceneManager::renderableList.end (); ++iter){

				// Check Pointer Value
				if (*iter == Object){

					SceneManager::renderableList.erase (iter);
					break;
				}
			}
		}

/*============================================================================================================*/

		// Remove Batch Group
		void SceneManager::Remove (optimization::BatchGroup* Object){

			// Loop Through Elements
			for (auto iter = SceneManager::batchGroupList.begin (); iter != SceneManager::batchGroupList.end (); ++iter){

				// Check Pointer Value
				if (*iter == Object){

					SceneManager::batchGroupList.erase (iter);
					break;
				}
			}
		}

/*============================================================================================================*/

		// Remove Skybox
		void SceneManager::Remove (Skybox* Object){

			// Loop Through Elements
			for (auto iter = SceneManager::skyboxList.begin (); iter != SceneManager::skyboxList.end (); ++iter){

				// Check Pointer Value
				if (*iter == Object){

					SceneManager::skyboxList.erase (iter);
					break;
				}
			}
		}

/*============================================================================================================*/

		// Update And Draw Objects
		void SceneManager::DrawAll (Camera* Camera, Material* PostPass){

			// Bind FBO And Clear It
			glBindFramebuffer (GL_DRAW_FRAMEBUFFER, SceneManager::frameGBuffer);
			glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Draw All Objects
			SceneManager::DrawSkybox (Camera);
			SceneManager::DrawBatchGroups (Camera);
			SceneManager::DrawRenderables (Camera);

			// Unbind FBO
			glBindFramebuffer (GL_DRAW_FRAMEBUFFER, 0);

			// Draw Fullscreen Plane
			glDisable (GL_DEPTH_TEST);
			SceneManager::DrawGBuffer (PostPass);
			glEnable (GL_DEPTH_TEST);
		}

/*============================================================================================================*/
/*------PRIVATE FUNCTIONS-------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Draw The GBuffer
		void SceneManager::DrawGBuffer (Material* Material){

			// Set Window Size
			Material -> SetUniform ("WindowSize", glm::vec2 (Window::width, Window::height));

			// Bind The Material
			Material -> Bind (true);

			// Set Textures
			SceneManager::textureGBuffer -> BindAll (Material);

			// Bind VAO And Draw Fullscreen Quad
			glBindVertexArray (SceneManager::arrayGBuffer);
			glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray (0);

			// Unbind The Material
			Material -> Bind (false);
		}

/*============================================================================================================*/

		// Draw All Skyboxes
		void SceneManager::DrawSkybox (Camera* Camera){

			// Check If There Are Objects To Render
			if (SceneManager::skyboxList.size () > 0){

				// Disable Depth Testing
				glDisable (GL_DEPTH_TEST);

				// Draw All Skyboxes
				for (auto object : SceneManager::skyboxList)
					object -> Draw (Camera);

				// Enable Depth Testing
				glEnable (GL_DEPTH_TEST);
			}
		}

/*============================================================================================================*/

		// Draw Batch Groups
		void SceneManager::DrawBatchGroups (Camera* Camera){

			for (auto object : SceneManager::batchGroupList){

				// Check If Group Contains Items
				if (object -> meshList.size () > 0)
					object -> Draw (Camera);
			}
		}

/*============================================================================================================*/

		// Draw Renderables
		void SceneManager::DrawRenderables (Camera* Camera){

			for (auto object : SceneManager::renderableList)
				object -> Draw (Camera);
		}

/*============================================================================================================*/
/*------DESTRUCTOR--------------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Destroy The SceneManager
		SceneManager::~SceneManager (){

			glDeleteVertexArrays (1, &arrayGBuffer);
			glDeleteBuffers		 (1, &vertexGBuffer);
			glDeleteFramebuffers (1, &frameGBuffer);
		}
	}
}
