#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform float time;

void GenerateTriangle(float d) {
	vec4 v1 = gl_in[0].gl_Position - gl_in[1].gl_Position;
	vec4 v2 = gl_in[1].gl_Position - gl_in[2].gl_Position;
	vec4 explosionNormal = vec4(normalize(-1 * cross(vec3(v1), vec3(v2))), 0);
	gl_Position = gl_in[0].gl_Position + explosionNormal * d;
	EmitVertex();
	gl_Position = gl_in[1].gl_Position + explosionNormal * d;
	EmitVertex();
	gl_Position = gl_in[2].gl_Position + explosionNormal * d;
	EmitVertex();
	EndPrimitive();
}

void main(){
	GenerateTriangle(time);
}