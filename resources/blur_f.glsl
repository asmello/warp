#version 410

layout(location = 0) in vec2 v_texcoord;

layout(location = 0) out vec4 outColor;

uniform sampler2D u_sampler0;
uniform bool horizontal;
uniform float weight[7] = float[] (0.00598, 0.060626, 0.241843, 0.383103, 0.241843, 0.060626, 0.00598);

void main()
{
    float scale = 2.6;
    float strength = 0.53;
    vec2 tex_offset = 1.0 / textureSize(u_sampler0, 0) * scale; // gets size of single texel
    vec3 result = texture(u_sampler0, v_texcoord).rgb * weight[0]; // current fragment's contribution
    if (horizontal)
    {
        for (int i = 1; i < 7; ++i)
        {
            float factor = strength * weight[i];
            vec2 offset = vec2(tex_offset.x * i, 0.0);
            result += texture(u_sampler0, v_texcoord + offset).rgb * factor;
            result += texture(u_sampler0, v_texcoord - offset).rgb * factor;
        }
    }
    else
    {
        for (int i = 1; i < 7; ++i)
        {
            float factor = strength * weight[i];
            vec2 offset = vec2(0.0, tex_offset.y * i);
            result += texture(u_sampler0, v_texcoord + offset).rgb * factor;
            result += texture(u_sampler0, v_texcoord - offset).rgb * factor;
        }
    }
    outColor = vec4(result, 1.0);
}
