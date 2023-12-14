#version 330 core

in vec2 uv;

#define numWeights 10 
out vec4 FragColor;

uniform sampler2D defaultTexture;

float weight[numWeights] = float[](0.27252216614968922, 0.27222107499168723, 0.26775787555338278, 0.258197196202193, 0.24925209073393424,
    0.23850496516196473, 0.22621814696803258, 0.19070115902322094, 0.1753817278195756, 0.16763484915651723);

void main()
{

	//vec3 result = texture(defaultTexture, uv).rgb;
	//FragColor = vec4(result, 1.0);

    vec2 tex_offset = 1.0 / textureSize(defaultTexture, 0); // gets size of single texel
    vec3 result = texture(defaultTexture, uv).rgb * weight[0];
    for (int i = 1; i < numWeights; ++i)
    {
        result += texture(defaultTexture, uv + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        result += texture(defaultTexture, uv - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
    }
    for (int i = 1; i < numWeights; ++i)
    {
        result += texture(defaultTexture, uv + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        result += texture(defaultTexture, uv - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
    }

  /*  vec3 grayscale = vec3(.5, .5, .5);
    result += vec3(dot(texture(defaultTexture, uv).rgb, grayscale));*/
    result = result / numWeights;;
    FragColor = vec4(result, 1.0);
}