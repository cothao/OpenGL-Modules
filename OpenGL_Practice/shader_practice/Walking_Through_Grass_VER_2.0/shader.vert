#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in mat4 positions;

out VS_OUT {
    vec3 normal;
//    float magnitude;
} vs_out;

uniform mat4 model;
uniform mat4 view;

out vec3 FragPos;
out vec2 texCoords;

float rand(vec2 co)
{
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}


void main()
{    
    mat3 normalMatrix = mat3(transpose(inverse(view * positions)));
//    vs_out.magnitude = clamp(rand((vec4(aPos, 1.) * positions).xz) * 2, 0., 70.);
    gl_Position = view * positions * vec4(aPos, 1.0); 
    FragPos = vec3(positions * vec4(aPos, 1.));
    texCoords = aTexCoords;
}