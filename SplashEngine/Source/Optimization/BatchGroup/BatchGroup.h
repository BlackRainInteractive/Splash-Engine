//============================================================================
// Name        : BatchGroup.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include <vector>

// The Splash Engine Namespace
namespace se{

	// Forward Declare Rendering Classes
	namespace rendering{

		class Camera;
		class Mesh;
	}

//============================================================================

	// The Optimization Namespace
	namespace optimization{

		// The Batch Group Class
		class BatchGroup{

			// Functions
			void Add (rendering::Mesh* Mesh);
			void Remove (rendering::Mesh* Mesh);

			// Variables
			std::vector <rendering::Mesh*> meshList;
		};
	}
}
