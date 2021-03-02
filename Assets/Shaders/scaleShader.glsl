#version 400 core

uniform mat4 modelMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projMatrix = mat4(1.0f);

uniform float time = 0.0f;

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 colour;
layout (location = 2) in vec2 texCoord;
out Vertex
{
	vec4 colour;
	vec2 texCoord;
} OUT;

mat4 scale(){
		return mat4(vec4(0.2,0,0,0), //scales x
				vec4(0,0.2f,0,0), //scales y
				vec4(0,0,0.2f,0), //scales z
				vec4(0,0,0,0.2f)); //changes overall scale
}

void main (void)
{
	float fastTime = time*time; //makes things move faster the more time has gone by
	mat4 mvp = (projMatrix * viewMatrix * modelMatrix);
	
	if(time>0.5){ //doesnt start the shrinking immediately (mainly for screenshoting)
		gl_Position = mvp*vec4(position,fastTime)*scale();
	}

	OUT.texCoord = texCoord;
	OUT.colour = colour;
}
