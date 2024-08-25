#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;


void main()
{
    // linearly interpolate between both textures (20% container, 80% awesomeface)
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.8);
}