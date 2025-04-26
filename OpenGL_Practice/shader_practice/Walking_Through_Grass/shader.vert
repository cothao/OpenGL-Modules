#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in mat4 positions;

out VS_OUT {
    vec3 normal;
    vec3 WorldPos;
    vec3 FragPos;
    float randomCurve;
    
//    float magnitude;
} vs_out;

uniform mat4 model;
uniform mat4 view;


float rand(vec2 co)
{
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}


void main()
{    
    mat3 normalMatrix = mat3(transpose(inverse(view * positions)));
    vs_out.normal = vec3(vec4(normalMatrix * aNormal, 0.0));
//    vs_out.magnitude = clamp(rand((vec4(aPos, 1.) * positions).xz) * 2, 0., 70.);
    gl_Position = view * positions * vec4(aPos, 1.0); 
    vs_out.FragPos = vec3(view * positions * vec4(aPos, 1.));
    vs_out.WorldPos = (positions * vec4(aPos, 1.)).xyz;
    vs_out.randomCurve = rand(vs_out.WorldPos.xy) * 15.;
}