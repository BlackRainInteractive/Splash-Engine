#version 330

// Out Layouts
layout (location = 0) out vec3 DiffuseOut; 

// Uniforms
uniform vec3 Colour;

// The Main Function
void main (){
	DiffuseOut = Colour;
}
