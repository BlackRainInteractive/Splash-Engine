#version 330

// Out Layouts
layout (location = 0) out vec3 DiffuseOut; 
layout (location = 3) out vec3 PositionOut;

// In Variables
in vec3 UV;
in vec4 WorldPos;

// Uniforms
uniform samplerCube DiffuseTexture;

// The Main Function
void main (){

	DiffuseOut   = texture (DiffuseTexture, UV).xyz;
	PositionOut  = WorldPos.xyz;
}
