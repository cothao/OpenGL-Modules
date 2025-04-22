#version 330 core

in vec3 FragPos;
in vec2 texCoords;

vec3 lightPos = vec3(10., 10., 10.);
vec3 lightColor = vec3(0., 1., 1.);

uniform sampler2D texture_diffuse;

void main()
{    

    gl_FragColor = texture(texture_diffuse, texCoords);
}