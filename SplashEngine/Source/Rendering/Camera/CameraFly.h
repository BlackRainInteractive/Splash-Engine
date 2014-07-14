//============================================================================
// Name        : CameraFly.h
// Author      : Kyle Finlay
// Copyright   : 2014 by Black Rain Interactive
// Description : This file is a part of Splash Engine.
//============================================================================

#pragma once

#include "Camera.h"

// The Splash Engine Namespace
namespace se{

	// The Rendering Namespace
	namespace rendering{

		// The Fly Camera Class
		class CameraFly : public Camera{
		public:

			// Functions - Setup
			void SetupCamera (CAMERA_MODE CameraMode, float MoveSpeed, float LookSpeed);

			// Functions - Updating
			virtual void Update ();

			// Variables
			float moveSpeed;
			float lookSpeed;

		protected:

			// Functions - Updating
			void UpdateView ();
		};
	}
}
