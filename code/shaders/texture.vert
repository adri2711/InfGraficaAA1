#version 330

in vec3 in_Position;
in vec2 in_UV;
in vec3 in_Normal;

uniform mat4 objMat;
uniform mat4 mv_Mat;
uniform mat4 mvpMat;

out vec2 texCoord;
out vec4 vert_Normal;

void main() {
	gl_Position = mvpMat * objMat * vec4(in_Position, 1.0);
	texCoord = in_UV;
	vert_Normal = mv_Mat * objMat * vec4(in_Normal, 0.0);
}