#version 330

const float MAGNITUDE = 0.4f;

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in vec3 vert_Normal[];

void GenerateLine(int index){
	gl_Position = gl_in[index].gl_Position;
	EmitVertex();
	gl_Position = gl_in[index].gl_Position + vec4(vert_Normal[index], 0.f) * MAGNITUDE;
	EmitVertex();
	EndPrimitive();
}

void main(){
	GenerateLine(0);
	GenerateLine(1);
	GenerateLine(2);
}