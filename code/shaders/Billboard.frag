#version 330

in vec2 texCoord;

out vec4 out_Color;

uniform sampler2D ourTexture;

void main() {
	vec4 c = texture(ourTexture, texCoord);
	if (c.a < 0.9) 
		discard;
	out_Color = c;
}