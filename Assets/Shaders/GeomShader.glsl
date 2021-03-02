#version 330 core

float coordinates = 2.5;
uniform float time = 0.0f;


layout(triangles) in;
layout(triangle_strip, max_vertices = 14) out;

uniform mat4 modelMatrix 	= mat4(1.0f);
uniform mat4 viewMatrix 	= mat4(1.0f);
uniform mat4 projMatrix 	= mat4(1.0f);

float scale = 1;
in Vertex{
	vec4 colour;
	vec2 texCoord;
	mat4 mvp;
}IN[];

out Vertex{
	vec4 colour;
	vec2 texCoord;
	mat4 mvp;
}OUT;

void main() {
	mat4 mvp = (projMatrix * viewMatrix * modelMatrix);
	for (int i = 0; i < gl_in.length(); ++i) {
		OUT.colour = IN[i].colour;

	if(time >2 &&time<7){
		coordinates = coordinates -(0.3*time);
	}else if(time >=5){
		coordinates = 0.4;
	}

		// Front top left
		gl_Position = mvp * (gl_in[i].gl_Position + vec4(-coordinates, coordinates, coordinates,scale));
		OUT.texCoord = vec2(1, 1);
		EmitVertex();

		// Front top right
		gl_Position = mvp * (gl_in[i].gl_Position + vec4(coordinates, coordinates, coordinates ,scale));
		OUT.texCoord = vec2(1, 0);
		EmitVertex();

		// Front bottom left
		gl_Position = mvp * (gl_in[i].gl_Position + vec4(-coordinates , -coordinates , coordinates ,scale));
		OUT.texCoord = vec2(0, 1);
		EmitVertex();

		// Front bottom right
		gl_Position = mvp *(gl_in[i].gl_Position + vec4( coordinates , -coordinates , coordinates ,scale));
		OUT.texCoord = vec2(0, 0);
		EmitVertex();



		// Back bottom right
		gl_Position = mvp *(gl_in[i].gl_Position + vec4( coordinates , -coordinates , -coordinates ,scale));
		OUT.texCoord = vec2(1, 0);
		EmitVertex();

		// Front top right
		gl_Position = mvp *(gl_in[i].gl_Position + vec4( coordinates , coordinates , coordinates ,scale));
		OUT.texCoord = vec2(0, 1);
		EmitVertex();

		// Back top right
		gl_Position = mvp *(gl_in[i].gl_Position + vec4( coordinates , coordinates , -coordinates ,scale));
		OUT.texCoord = vec2(1, 1);
		EmitVertex();
		
		// Front top left
		gl_Position = mvp *(gl_in[i].gl_Position + vec4( -coordinates , coordinates , coordinates ,scale));
		OUT.texCoord = vec2(0, 0);
		EmitVertex();


		// Back top left
		gl_Position = mvp *(gl_in[i].gl_Position + vec4( -coordinates , coordinates , -coordinates ,scale));
		OUT.texCoord = vec2(1, 0);
		EmitVertex();

		// Front bottom left
		gl_Position = mvp *(gl_in[i].gl_Position + vec4( -coordinates , -coordinates , coordinates ,scale));
		OUT.texCoord = vec2(0, 1);
		EmitVertex();


		// Back bottom left
		gl_Position = mvp *(gl_in[i].gl_Position + vec4(  -coordinates , -coordinates , -coordinates ,scale));
		OUT.texCoord = vec2(1, 1);
		EmitVertex();
	
		// Back bottom right
		gl_Position = mvp *(gl_in[i].gl_Position + vec4( coordinates , -coordinates , -coordinates ,scale));
		OUT.texCoord = vec2(1, 0);
		EmitVertex();

		// Back top left
		gl_Position = mvp *(gl_in[i].gl_Position + vec4(-coordinates , coordinates , -coordinates , scale));
		OUT.texCoord = vec2(0, 1);
		EmitVertex();
	
		// Back top right
		gl_Position = mvp *(gl_in[i].gl_Position + vec4(coordinates , coordinates , -coordinates ,scale));
		OUT.texCoord = vec2(0, 0);
		EmitVertex();
	
		EndPrimitive();

	}
}