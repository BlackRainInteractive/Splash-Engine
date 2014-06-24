#version 330

// Out Layouts
layout (location = 0) out vec3 DiffuseOut;
layout (location = 3) out vec3 PositionOut;

// In Variables
in vec3 gWorldPos;
in vec3 gEdgeDistance;

// Uniforms
uniform vec3 Colour;

// Variables
float lineWidth = 0.25;

// The Main Function
void main (){

	// Get The Min Edge Distance
	float dist = min (gEdgeDistance.x, gEdgeDistance.y);
	dist = min (dist, gEdgeDistance.z);

	// Find The Colour Mix Value
	float mixValue = smoothstep (lineWidth - 1, lineWidth + 1, dist);

	DiffuseOut   = mix (vec3 (0), Colour, mixValue);
	PositionOut  = gWorldPos.xyz;
}
