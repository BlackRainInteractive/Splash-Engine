#version 330

// Mesh Layouts
layout (location = 0) in vec3 VertexPos;

// Out Variables
out vec3 vUV;
out vec4 vWorldPos;

// Uniforms
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

// The Main Function
void main (){
	
	// Set Vertex Position
	gl_Position = (P * V * M) * vec4 (VertexPos, 1);
	
	// Set UV Coords, Normals, And World Pos
	vUV = -VertexPos;
	vWorldPos = vec4 (VertexPos, 1.0);
}