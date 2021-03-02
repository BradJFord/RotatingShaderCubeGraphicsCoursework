#version 400 core
layout (vertices =4) out; // num vertices in output patch
uniform float time = 0.0f;
in Vertex {
vec2 texCoord; // From Vertex Shader
}IN[]; // Equal to size of the draw call vertex count

out Vertex {
vec2 texCoord; // To Evaluation Shader
}OUT[]; // Equal to the size of the layout vertex count

void main() {
gl_TessLevelInner [0] = (2*time)*2;
gl_TessLevelInner [1] = (2*time)*2;
gl_TessLevelOuter [0] = (2*time)*2;
gl_TessLevelOuter [1] = (2*time)*2;
gl_TessLevelOuter [2] = (2*time)*2;
gl_TessLevelOuter [3] = (2*time)*2;

OUT [gl_InvocationID].texCoord = IN[gl_InvocationID].texCoord;

gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID ].gl_Position;
}
