#version 330

uniform mat4 objMat;
uniform mat4 mvpMat;

layout(triangles) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 cameraRotation;
float quadSize = 3;

void GenerateQuad(float size) {
    gl_Position = gl_in[0].gl_Position + mvpMat * objMat * vec4(0, size/2, size/2, 0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + mvpMat * objMat * vec4(0, -size/2, size/2, 0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + mvpMat * objMat * vec4(0, size/2, -size/2, 0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + mvpMat * objMat * vec4(0, -size/2, -size/2, 0);
    EmitVertex();
    EndPrimitive();
}

void main(){
    GenerateQuad(quadSize);
}