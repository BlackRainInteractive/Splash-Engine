//============================================================================
// Name        : BatchGroup.cpp
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#include "BatchGroup.h"
#include "../../Rendering/Camera/Camera.h"
#include "../../Rendering/Material/Material.h"
#include "../../Rendering/Mesh/Mesh.h"
#include "../../Rendering/Texture/Texture.h"
#include <GL/glew.h>

// The Splash Engine Namespace
namespace se{

	// The Optimization Namespace
	namespace optimization{

/*============================================================================================================*/
/*------PUBLIC FUNCTIONS--------------------------------------------------------------------------------------*/
/*============================================================================================================*/

		// Add A Mesh To The Group
		void BatchGroup::Add (rendering::Mesh* Mesh){
			BatchGroup::meshList.push_back (Mesh);
		}

/*============================================================================================================*/

		// Remove A Mesh From Thr Group
		void BatchGroup::Remove (rendering::Mesh* Mesh){

			// Loop Through Elements
			for (auto iter = BatchGroup::meshList.begin (); iter != BatchGroup::meshList.end (); ++iter){

				// Check Pointer Value
				if (*iter == Mesh){

					BatchGroup::meshList.erase (iter);
					break;
				}
			}
		}

/*============================================================================================================*/

		// Draw The Meshes
		void BatchGroup::Draw (rendering::Camera* Camera){

			// Set The Camera Transforms
			BatchGroup::meshList[0] -> material -> SetUniform ("V", Camera -> vMatrix);
			BatchGroup::meshList[0] -> material -> SetUniform ("P", Camera -> pMatrix);

			// Bind The Material
			BatchGroup::meshList[0] -> material -> Bind (true);

			// Loop Through All Mesh Data
			for (auto meshData : BatchGroup::meshList[0] -> meshData){

				// Pass Texture Data
				meshData.texture -> BindAll (BatchGroup::meshList[0] -> material);

				// Bind VAO
				glBindVertexArray (meshData.arrayBuffer);

				// Loop Through Total Meshes
				for (unsigned int i = 0; i < BatchGroup::meshList.size (); ++i){

					// Set Model Matrix
					BatchGroup::meshList[0] -> material -> SetUniform ("M", BatchGroup::meshList[i] -> GetParentTransforms () * BatchGroup::meshList[i] -> mMatrix);

					// Draw
					glDrawElements (GL_TRIANGLES, meshData.indices.size (), GL_UNSIGNED_INT, nullptr);
				}

				// Unbind VAO
				glBindVertexArray (0);
			}

			// Unbind Material
			BatchGroup::meshList[0] -> material -> Bind (false);
		}
	}
}