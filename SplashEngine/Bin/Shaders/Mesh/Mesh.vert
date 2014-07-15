#version 330

// Mesh Layouts
layout (location = 0) in vec3 VertexPos;
layout (location = 1) in vec2 TexCoord1;
layout (location = 2) in vec3 NormalPos;
layout (location = 3) in vec3 TangentPos;
layout (location = 4) in vec3 BitangentPos;

// Out Variables
out vec2 vUV1;
out vec3 vNormals;
out vec3 vTangents;
out vec3 vBitangents;
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
	vUV1	    = TexCoord1;
	vNormals    = NormalPos;
	vTangents   = TangentPos;
	vBitangents = BitangentPos;
	vWorldPos   = (V * M * (vec4 (VertexPos, 1.0)));
}