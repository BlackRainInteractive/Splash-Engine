#version 330
 
// Layouts
layout (location = 0) in vec3 VertexPos;

// The Main Function
void main(){
    gl_Position = vec4 (VertexPos, 1.0);
}