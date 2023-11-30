#version 330 core

in vec2 uv;

out vec4 FragColor;

uniform sampler2D defaultTexture;

void main()
{
	//vec2 tex_offset = 1.0 / textureSize(defaultTexture, 0); // gets size of single texel
	vec3 result = texture(defaultTexture, uv).rgb;
	FragColor = vec4(result, 1.0);
}