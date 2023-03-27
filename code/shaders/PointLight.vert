#version 330

in vec3 in_position;

uniform mat4 objectMatrix;
uniform mat4 mv_Matrix;
uniform mat4 mvpMatrix;
uniform vec4 lightColor;

void main() {
    gl_Position = mvpMatrix * objectMatrix * vec4(in_position, 1.0);
}