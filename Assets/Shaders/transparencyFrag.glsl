#version 400 core
uniform sampler2D tex;
uniform float time = 0.0f;
in Vertex{
	smooth vec4 colour;
	smooth vec2 texCoord;
}IN;
out vec4 fragColor;

void main(void) {
	vec3 fragPos = gl_FragCoord.rgb;

	float r = fragPos.x;
	float g = fragPos.y;
	float b = fragPos.z;

	float alphaVal = 1 -(time * 0.1);
	fragColor = vec4(r,g,b,alphaVal);
}