#version 330

out vec2 texCoord;

uniform mat4 objectMatrix;
uniform mat4 mvpMatrix;
uniform mat4 mv_Matrix;

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 cameraRotation;
float quadSize = 3;

void GenerateQuad(float size) {
    gl_Position = mvpMatrix * objectMatrix * (gl_in[0].gl_Position + vec4(size/2, size/2, 0, 0));
    texCoord = vec2(1,1);
    EmitVertex();
    gl_Position = mvpMatrix * objectMatrix * (gl_in[0].gl_Position + vec4(size/2, -size/2, 0, 0));
    texCoord = vec2(1,0);
    EmitVertex();
    gl_Position = mvpMatrix * objectMatrix * (gl_in[0].gl_Position + vec4(-size/2, size/2, 0, 0));
    texCoord = vec2(0,1);
    EmitVertex();
    gl_Position = mvpMatrix * objectMatrix * (gl_in[0].gl_Position + vec4(-size/2, -size/2, 0, 0));
    texCoord = vec2(0,0);
    EmitVertex();
    EndPrimitive();
}

void main(){
    vec4 camBillboardVec = mv_Matrix * objectMatrix * gl_in[0].gl_Position; //Vector between cam and billboard in cam space
    vec4 auxVec = camBillboardVec + vec4(0, 1, 0, 0); //Vector between cam and billboard in cam space
    GenerateQuad(quadSize);
}