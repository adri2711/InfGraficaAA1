#version 330

in vec3 in_Position;
in vec3 in_Normal;

uniform mat4 mv_Matrix;
uniform mat4 mvpMatrix;
uniform mat4 objectMatrixArray[10];

out vec4 vert_Normal;

void main() {
	mat4 offset = objectMatrixArray[gl_InstanceID];
	gl_Position = mvpMatrix * offset * vec4(in_Position, 1.0);
	vert_Normal = mv_Matrix * offset * vec4(in_Normal, 0.0);
}