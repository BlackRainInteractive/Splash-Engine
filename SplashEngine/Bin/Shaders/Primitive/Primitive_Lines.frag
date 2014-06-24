#version 330

// Out Layouts
layout (location = 0) out vec3 DiffuseOut;
layout (location = 3) out vec3 PositionOut;

// In Variables
in vec3 vWorldPos;

// Uniforms
uniform vec3 Colour;

// The Main Function
void main (){

	DiffuseOut   = Colour;
	PositionOut  = vWorldPos.xyz;
}
