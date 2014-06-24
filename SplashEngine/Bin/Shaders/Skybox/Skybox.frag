#version 330

// Out Layouts
layout (location = 0) out vec3 DiffuseOut; 
layout (location = 3) out vec3 PositionOut;

// In Variables
in vec3 vUV;
in vec4 vWorldPos;

// Uniforms
uniform samplerCube DiffuseTexture;

// The Main Function
void main (){

	DiffuseOut   = texture (DiffuseTexture, vUV).xyz;
	PositionOut  = vWorldPos.xyz;
}
