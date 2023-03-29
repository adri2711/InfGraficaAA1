#version 330

in vec4 vert_Normal;
in vec3 FragPos;
out vec4 out_Color;

uniform mat4 mv_Mat;
uniform vec4 color;
uniform vec3 _lightPosition;
uniform vec4 _lightColor;
uniform float _radiantPower;
uniform float _ambientReflectionCoefficient;
uniform float _diffuseReflectionCoefficient;
uniform float _specularReflectionCoefficient;
uniform float _shininessCoefficient;

void main() {
	
	vec3 normal = vec3(vert_Normal);	
	vec3 coordinate = vec3(FragPos);	
	vec3 lightDirection = normalize(_lightPosition - coordinate);
	
	vec4 ambientReflection = _ambientReflectionCoefficient * _lightColor;

	//vec4 diffuseReflection = _diffuseReflectionCoefficient * dot(normal, lightDirection) * _lightColor;
	vec4 diffuseReflection = ((_diffuseReflectionCoefficient * dot(normal, lightDirection)) * (_radiantPower/(4 * 3.14 * pow(length(lightDirection - coordinate), 2.f)))) * _lightColor;	
	
	vec4 specularReflection = _specularReflectionCoefficient * pow(dot(vec3(0.f, 0.f, 0.f) - coordinate, 2 * dot(normal, lightDirection) * normal - lightDirection), _shininessCoefficient) * _lightColor;
	//vec4 specularReflection = _specularReflectionCoefficient * pow(max(dot(normalize(vec3(0.f, 0.f, 0.f) - coordinate), reflect(-lightDirection, normal)), _shininessCoefficient.f), 0.0f) * _lightColor;
	//2 * dot(normal, lightDirection) * normal - lightDirection)
	vec4 lightResult = ambientReflection + (diffuseReflection + specularReflection) * (_radiantPower/(4 * 3.14 * pow(length(lightDirection - coordinate), 2.f)));
	
	out_Color =  (ambientReflection + diffuseReflection) * color;
}