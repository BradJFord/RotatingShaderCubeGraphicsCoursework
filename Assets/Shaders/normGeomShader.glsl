#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;
uniform float time;

in Vertex {
	vec4 colour;
    vec2 texCoord;
	mat4 mvp;
	
} IN[];
out Vertex{
	vec4 colour;
	vec2 texCoord;
	mat4 mvp;
}OUT;


void main() {  

	vec3 a = vec3(gl_in[0].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position)*a;
    vec3 c = vec3(gl_in[1].gl_Position)*b;
   vec3 normal = normalize(cross(a*50,c));

	OUT.colour = IN[0].colour;
    gl_Position = (gl_in[0].gl_Position + vec4(((normal*3) * sin(time) * cos(time)),5.0));
    OUT.texCoord = IN[0].texCoord;
    EmitVertex();
	OUT.colour = IN[1].colour;
    gl_Position =(gl_in[1].gl_Position + vec4(((normal*3) * sin(time)* cos(time)),5.0));
    OUT.texCoord = IN[1].texCoord;
    EmitVertex();
	OUT.colour = IN[2].colour;
    gl_Position = (gl_in[2].gl_Position + vec4(((normal*3) * sin(time)* cos(time)),5.0));
    OUT.texCoord = IN[2].texCoord;
    EmitVertex();
    EndPrimitive();
}  