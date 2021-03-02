#version 400 core
uniform sampler2D mainTex; // old texture , on Tex Unit 0
uniform sampler2D secondTex; // new texture , on Tex Unit 1

uniform float time; // From the previous tutorial !

in Vertex
{
	vec4 colour;
	vec2 texCoord;
}IN;

out vec4 fragColor;

void main(void) {
	vec4 tex1 = texture(mainTex, IN.texCoord);
	vec4 tex2 = texture(secondTex, IN.texCoord);
	if(time <10){

	fragColor = mix(tex1, tex2, time/10);
	
	}else{
		fragColor = mix(tex1, tex2, 1);
	}
}