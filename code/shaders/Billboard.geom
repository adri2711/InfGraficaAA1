#version 330

out vec2 texCoord;

uniform mat4 objectMatrix;
uniform mat4 mvpMatrix;
uniform mat4 mv_Matrix;
uniform mat4 pMatrix;
uniform float quadSize = 3;

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

void GenerateQuad(vec4 hDir, vec4 vDir, float size) {
    gl_Position = mvpMatrix * objectMatrix * gl_in[0].gl_Position + pMatrix * (hDir * size / 2 + vDir * size / 2);
    texCoord = vec2(1,1);
    EmitVertex();
    gl_Position = mvpMatrix * objectMatrix * gl_in[0].gl_Position + pMatrix * (hDir * size / 2 + -vDir * size / 2);
    texCoord = vec2(1,0);
    EmitVertex();
    gl_Position = mvpMatrix * objectMatrix * gl_in[0].gl_Position + pMatrix * (-hDir * size / 2 + vDir * size / 2);
    texCoord = vec2(0,1);
    EmitVertex();
    gl_Position = mvpMatrix * objectMatrix * gl_in[0].gl_Position + pMatrix * (-hDir * size / 2 + -vDir * size / 2);
    texCoord = vec2(0,0);
    EmitVertex();
    EndPrimitive();
}

void main(){
    vec4 camBillboardVec = mv_Matrix * objectMatrix * gl_in[0].gl_Position; //Vector between cam and billboard in cam space
    vec4 auxVec = camBillboardVec + vec4(0, 1, 0, 0);
    vec4 hDir = normalize(vec4(cross(camBillboardVec.xyz, auxVec.xyz), 0));
    vec4 vDir = normalize(vec4(cross(camBillboardVec.xyz, hDir.xyz), 0));
    GenerateQuad(hDir, vDir, quadSize);
}