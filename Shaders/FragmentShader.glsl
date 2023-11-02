#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 posInWS;
in vec2 uv;

uniform vec3 viewPos;
//Material Props
//uniform vec3 objectColour;
uniform float shine;
//uniform float specStrength;
uniform sampler2D diffuseMap;
uniform sampler2D specularMap;


//Directional Light
uniform vec3 lightColour;
uniform vec3 lightDirection;
uniform float ambientFactor;

//Point Light
uniform vec3 plightPosition;
uniform vec3 plightColour;
uniform vec3 pAttentuation;

//Spot Light
uniform vec3 slightPosition;
uniform vec3 slightColour;
uniform vec3 sAttentuation;
uniform vec3 sDirection;
uniform vec2 sRadii;

//struct pointLight {
	//vec3 colour;
	//vec3 position;
	//vec3 constants;
//};

//#define numPL 2
//uniform pointLight[numPL];

vec3 n = normalize(normal);
vec3 viewDir = normalize(viewPos - posInWS);

vec3 getDirectionalLight();
vec3 getPointLight();
vec3 getSpotLight();


void main()
{

	vec3 result = getDirectionalLight();
	result += getPointLight();
	FragColor = vec4(result, 1.0); //RGBA

}

vec3 getDirectionalLight()
{

	vec3 objCol = texture(diffuseMap, uv).rgb;
	float specStrength = texture(specularMap, uv).r;

	vec3 ambient = objCol * lightColour * ambientFactor;

	float diffuseFactor = dot(n, -lightDirection);
	diffuseFactor = max(diffuseFactor, 0.0f);
	vec3 diffuse = objCol * lightColour * diffuseFactor;

	vec3 H = normalize(-lightDirection + viewDir);
	float specLevel = dot(n, H);
	specLevel = max(specLevel, 0.0);
	specLevel = pow(specLevel, shine);
	vec3 specular = lightColour * specLevel * specStrength;

	return ambient + diffuse + specular;
}

vec3 getPointLight()
{
	vec3 objCol = texture(diffuseMap, uv).rgb;
	float specStrength = texture(specularMap, uv).r;

	float distance = length(plightPosition - posInWS);
	float attn = 1.0/(pAttentuation.x + (pAttentuation.y*distance) + (pAttentuation.z*(distance*distance)));

	vec3 lightDir = normalize((plightPosition - posInWS));

	float diffuseFactor = dot(n, lightDir);
	diffuseFactor = max(diffuseFactor, 0.0f);
	vec3 diffuse = objCol * plightColour * diffuseFactor;

	vec3 H = normalize(lightDir + viewDir);
	float specLevel = dot(n, H);
	specLevel = max(specLevel, 0.0);
	specLevel = pow(specLevel, shine);
	vec3 specular = plightColour * specLevel * specStrength;

	diffuse = diffuse * attn;
	specular = specular * attn;
	return diffuse + specular;
}

vec3 getSpotLight()
{
	vec3 objCol = texture(diffuseMap, uv).rgb;
	float specStrength = texture(specularMap, uv).r;

	float distance = length(slightPosition - posInWS);
	float attn = 1.0 / (sAttentuation.x + (sAttentuation.y * distance) + (sAttentuation.z * (distance * distance)));

	vec3 slightDir = normalize((slightPosition - posInWS));

	float diffuseFactor = dot(n, slightDir);
	diffuseFactor = max(diffuseFactor, 0.0f);
	vec3 diffuse = objCol * slightColour * diffuseFactor;

	vec3 H = normalize(slightDir + viewDir);
	float specLevel = dot(n, H);
	specLevel = max(specLevel, 0.0);
	specLevel = pow(specLevel, shine);
	vec3 specular = slightColour * specLevel * specStrength;

	diffuse = diffuse * attn;
	specular = specular * attn;

	float theta = dot(-slightDir, normalize(slightDir));
	float denom = (sRadii.x - sRadii.y);
	float intensity = (theta - sRadii.y) / denom;
	intensity = clamp(intensity, 0.0, 1.0);
	diffuse = diffuse * intensity;
	specular = specular * intensity;

	return diffuse + specular;
}