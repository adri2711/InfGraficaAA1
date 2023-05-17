#version 330

in vec2 texCoord;
in vec3 FragPos;
in vec4 vert_Normal;

out vec4 out_Color;

uniform sampler2D ourTexture;

uniform mat4 objMat;

uniform vec3 _lightPosition;
uniform vec3 _lightColor;

uniform float _radiantEffect;

uniform float _ambientReflectionCoefficient;
uniform float _diffuseReflectionCoefficient;
uniform float _specularReflectionCoefficient;

uniform float _shininessCoefficient;

void main() {

	vec3 normal = normalize(vec3(vert_Normal));
	vec3 coordinate = vec3(objMat * vec4(FragPos, 1.0f));

	vec3 lightVector = _lightPosition - coordinate;
	vec3 lightDirection = normalize(lightVector);
	vec3 lightVectorMirror = reflect(-lightDirection, normal);

	float radiance = _radiantEffect / pow(max(0.001f, length(lightVector)), 2.f);

	vec3 cameraVector = normalize(vec3(0.f, 0.f, 0.f) - coordinate);

	vec3 ambientReflection = _ambientReflectionCoefficient * _lightColor;

	vec3 diffuseReflection = _diffuseReflectionCoefficient * dot(normal, lightVector) * _lightColor;

	vec3 specularReflection = _specularReflectionCoefficient * pow(max(0.001f, dot(vec3(cameraVector), lightVectorMirror)), _shininessCoefficient) * _lightColor;

	vec3 lightResult = ambientReflection + (diffuseReflection + specularReflection) * radiance;
	
	out_Color = vec4(ambientReflection, 1.0f) * texture(ourTexture, texCoord);
}