#version 330

// Out Layouts
layout (location = 0) out vec3 DiffuseOut;
layout (location = 2) out vec3 NormalOut;
layout (location = 3) out vec3 PositionOut;

// In Variables
in vec2 vUV1;
in vec2 vUV2;
in vec3 vNormals;
in vec3 vTangents;
in vec3 vBitangents;
in vec4 vWorldPos;

// Uniforms
uniform sampler2D DiffuseTexture;
uniform mat4 M;

// The Main Function
void main (){

	DiffuseOut  = texture (DiffuseTexture, vUV1, 0).xyz;
	NormalOut   = vNormals;
	PositionOut = vWorldPos.xyz;
}
