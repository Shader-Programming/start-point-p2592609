#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 posInWS;

uniform vec3 viewPos;
uniform vec3 objectColour;
uniform vec3 lightColour;
uniform vec3 lightDirection;
uniform float ambientFactor;
uniform float shine;
uniform float specStrength;
uniform vec3 plightPosition;
uniform vec3 plightColour;
uniform vec3 pAttentuation;

struct pointLight {
	vec3 colour;
	vec3 position;
	vec3 constants;
};

//#define numPL 2
//uniform pointLight[numPL];

vec3 n = normalize(normal);
vec3 viewDir = normalize(viewPos - posInWS);

vec3 getDirectionalLight();
vec3 getPointLight();


void main()
{

	vec3 result = getDirectionalLight();
	result += getPointLight();
	FragColor = vec4(result, 1.0); //RGBA

}

vec3 getDirectionalLight()
{
	vec3 ambient = objectColour * lightColour * ambientFactor;

	float diffuseFactor = dot(n, -lightDirection);
	diffuseFactor = max(diffuseFactor, 0.0f);
	vec3 diffuse = objectColour * lightColour * diffuseFactor;

	vec3 H = normalize(-lightDirection + viewDir);
	float specLevel = dot(n, H);
	specLevel = max(specLevel, 0.0);
	specLevel = pow(specLevel, shine);
	vec3 specular = lightColour * specLevel * specStrength;

	return ambient + diffuse + specular;
}

vec3 getPointLight()
{
	float distance = length(plightPosition - posInWS);
	float attn = 1.0/(pAttentuation.x + (pAttentuation.y*distance) + (pAttentuation.z*(distance*distance)));

	vec3 lightDir = normalize((plightPosition - posInWS));

	float diffuseFactor = dot(n, lightDir);
	diffuseFactor = max(diffuseFactor, 0.0f);
	vec3 diffuse = objectColour * plightColour * diffuseFactor;

	vec3 H = normalize(lightDir + viewDir);
	float specLevel = dot(n, H);
	specLevel = max(specLevel, 0.0);
	specLevel = pow(specLevel, shine);
	vec3 specular = plightColour * specLevel * specStrength;

	diffuse = diffuse * attn;
	specular = specular * attn;
	return diffuse + specular;
}