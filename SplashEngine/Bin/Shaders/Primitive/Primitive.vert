#version 330

// In Layouts
layout (location = 0) in vec3 VertexPos;

// Out Variables
out vec3 vWorldPos;

// Uniforms
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

// The Main Function
void main (){
	
	// Set Vertex Position
	gl_Position = (P * V * M) * vec4 (VertexPos, 1);

	// Set World Position
	vWorldPos = (V * M * (vec4 (VertexPos, 1.0))).xyz;
}