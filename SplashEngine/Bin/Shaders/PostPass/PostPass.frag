#version 330

// Out Variables
out vec3 FragColour;

// Variables
vec2 fragUV;
vec3 linearColour;

// Uniforms
uniform sampler2D DiffuseBufferTexture;
uniform sampler2D SpecularBufferTexture;
uniform sampler2D NormalBufferTexture;
uniform sampler2D PositionBufferTexture;
uniform sampler2D DepthBufferTexture;
uniform vec2 WindowSize;

// The Main Function
void main (){
	
	// Get UVs (In Screen Coords)
	fragUV = gl_FragCoord.xy / vec2 (WindowSize.x, WindowSize.y);
	
	// Set Fragment Colour
	//if (texture (SpecularBufferTexture, fragUV) == vec4 (1))
		FragColour.rgb = texture (DiffuseBufferTexture, fragUV).xyz;

	//else
		//FragColour.rgb = texture (SpecularBufferTexture, fragUV).xyz;
}
