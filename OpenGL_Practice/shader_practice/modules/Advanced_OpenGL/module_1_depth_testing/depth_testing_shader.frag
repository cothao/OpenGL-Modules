
#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;

float near = 0.1;
float far = 100.;

float LinearizeDepth(float depth)
{
    float z = depth * 2. - 1.;
    return (2.0 * near * far)/(far + near - z * (far - near));
}

uniform sampler2D texture1;

void main()
{
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
    FragColor = vec4(vec3(depth), 1.);
} 