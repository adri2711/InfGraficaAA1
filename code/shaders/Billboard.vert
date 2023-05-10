#version 330

in vec3 in_Position;
in vec2 in_UV;

uniform mat4 objectMatrix;
uniform mat4 mvpMatrix;

out vec2 texCoord;

void main() {
	gl_Position = vec4(in_Position, 1.0);
	texCoord = in_UV;
}