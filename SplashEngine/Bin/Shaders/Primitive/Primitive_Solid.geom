#version 330

// In Layouts
layout (triangles) in;

// Out Layouts
layout (triangle_strip, max_vertices = 3) out;

// In Variables
in vec3 vWorldPos [];

// Out Variables
out vec3 gWorldPos;
out vec3 gEdgeDistance;

// Uniforms
uniform mat4 VP;

// The Main Function
void main (){

    // Transform Vertices Into Viewport Space
    vec3 p0 = vec3 (VP * (gl_in [0].gl_Position / gl_in [0].gl_Position.w));
    vec3 p1 = vec3 (VP * (gl_in [1].gl_Position / gl_in [1].gl_Position.w));
    vec3 p2 = vec3 (VP * (gl_in [2].gl_Position / gl_in [2].gl_Position.w));

    // Find The Vertex Altitudes
    float a = length (p1 - p2);
    float b = length (p2 - p0);
    float c = length (p1 - p0);

    float alpha = acos ((b * b + c * c - a * a) / (2.0 * b * c));
    float beta  = acos ((a * a + c * c - b * b) / (2.0 * a * c));

    float ha = abs (c * sin (beta));
    float hb = abs (c * sin (alpha));
    float hc = abs (b * sin (alpha));

    // Send Triangle 01 To Fragment Shader
    gEdgeDistance = vec3 (ha, 0, 0);
    gWorldPos     = vWorldPos [0];
    gl_Position   = gl_in [0].gl_Position;
    EmitVertex ();

    // Send Triangle 02 To Fragment Shader
    gEdgeDistance = vec3 (0, hb, 0);
    gWorldPos     = vWorldPos [1];
    gl_Position   = gl_in [1].gl_Position;
    EmitVertex ();

    // Send Triangle 03 To Fragment Shader
    gEdgeDistance = vec3 (0, 0, hc);
    gWorldPos     = vWorldPos [2];
    gl_Position   = gl_in [2].gl_Position;
    EmitVertex ();

    // End Of Primitive
    EndPrimitive ();
}
