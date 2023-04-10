#version 330

in vec3 in_Position;
in vec3 in_Normal;

uniform mat4 objectMatrix;
uniform mat4 mv_Matrix;
uniform mat4 mvpMatrix;

out vec4 vert_Normal;

void main() {
	gl_Position = mvpMatrix * objectMatrix * vec4(in_Position, 1.0);
	vert_Normal = mv_Matrix * objectMatrix * vec4(in_Normal, 0.0);
}