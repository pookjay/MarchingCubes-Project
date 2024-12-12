#version 330 core

out vec4 FragColor;

in vec3 Pos;
in vec3 Normal;
in vec3 Color;

uniform vec3 lightPosition;

vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);    
vec3 ambientColor = vec3(0.2f, 0.2f, 0.2f);  

void main()
{
    vec3 norm = normalize(Normal);

    // Ambient lighting
    vec3 ambient = ambientColor * Color;

    // Diffuse lighting
    vec3 lightDirection = normalize(lightPosition - Pos); 
    vec3 diffuse = 0.7f * max(dot(norm, lightDirection),0.0f) * Color;

    // Output
    FragColor = vec4(diffuse + ambient, 1.0);
}