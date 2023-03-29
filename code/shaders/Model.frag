#version 330

in vec4 vert_Normal;
in vec3 FragPos;
out vec4 out_Color;

uniform mat4 mv_Mat;
uniform vec4 color;
uniform mat4 objectMatrix;

uniform vec3 _lightPosition;
uniform vec4 _lightColor;

uniform float _radiantEffect;

uniform float _ambientReflectionCoefficient;
uniform float _diffuseReflectionCoefficient;
uniform float _specularReflectionCoefficient;

uniform float _shininessCoefficient;

void main() {
	
	vec3 normal = normalize(vec3(vert_Normal));	
	vec3 coordinate = vec3(objectMatrix * vec4(FragPos, 1.0f));	
	vec3 lightDirection = _lightPosition - coordinate;
	
	vec4 ambientReflection = _ambientReflectionCoefficient * _lightColor;

	float radiance = _radiantEffect / pow(max(0.001f, length(lightDirection)), 2.f);

	//vec4 diffuseReflection = _diffuseReflectionCoefficient * dot(normal, lightDirection) * _lightColor;
	vec4 diffuseReflection = ((_diffuseReflectionCoefficient * dot(normal, lightDirection)) * radiance) * _lightColor;	
	
	//vec4 specularReflection = _specularReflectionCoefficient * pow(dot(vec3(0.f, 0.f, 0.f) - coordinate, 2 * dot(lightDirection, normal) * normal - lightDirection), _shininessCoefficient) * _lightColor;
	vec4 specularReflection = _specularReflectionCoefficient * pow(max(0.001f, dot(normalize(vec3(0.f, 0.f, 0.f) - coordinate), reflect(-lightDirection, normal)), _shininessCoefficient.f)) * _lightColor;
	
	vec4 lightResult = ambientReflection + (diffuseReflection + specularReflection) * radiance;
	
	out_Color =  lightResult * color;
}