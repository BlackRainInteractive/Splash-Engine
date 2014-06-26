#version 330

// Out Variables
out vec4 FragColour;

// Variables
vec2 fragUV;

// Uniforms
uniform sampler2D diffuseTexture;
uniform vec2 WindowSize;
uniform vec4 discardColour;

// The Main Function
void main (){
	
	// Get UVs (In Screen Coords)
	fragUV = gl_FragCoord.xy / vec2 (WindowSize.x, WindowSize.y);
	
	// Set Fragment Colour
	//if (texture (diffuseTexture, fragUV) == discardColour)
		//discard;

	//else{

		FragColour.rgb = texture (diffuseTexture, fragUV).rgb;
		FragColour.a = 1;
	//}
}
