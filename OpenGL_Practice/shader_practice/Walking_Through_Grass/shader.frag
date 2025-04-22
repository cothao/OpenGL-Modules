#version 330 core

in vec4 fColor;
in vec3 FaceNormal;
in vec3 FragPos;

vec3 lightPos = vec3(10., 10., 10.);
vec3 lightColor = vec3(0., 1., 1.);

void main()
{    

    float ambientStrength = 0.1;
    float specularStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(FaceNormal);

    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(lightDir, norm), 0.);

    vec3 diffuse = diff * lightColor;

//    vec3 viewDir = normalize(viewPos - FragPos);
//    vec3 reflectDir = reflect(-lightDir, norm); 
//
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//    vec3 specular = specularStrength * spec * lightColor;  
//
//    vec3 result = (ambient + diffuse + specular) * objectColor;

    vec3 result = (ambient + diffuse) * vec3(fColor);

    gl_FragColor = vec4(result, 1.0);
    gl_FragColor = fColor;

}