#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D Texture_Diffuse1;
uniform sampler2D Texture_Diffuse2;
uniform sampler2D Texture_Diffuse3;
uniform sampler2D Texture_Specular1;
uniform sampler2D Texture_Specular2;

void main()
{    
    FragColor = texture(Texture_Diffuse1, TexCoords);
}