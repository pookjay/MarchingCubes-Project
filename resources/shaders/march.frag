#version 330 core

out vec4 FragColor;

in vec3 Pos;
in vec3 Normal;
in vec3 Color;

vec3 lightDir = vec3(1.0f, 1.0f, 1.0f);     
vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);    
vec3 ambientColor = vec3(0.2f, 0.2f, 0.2f);  

// Adjustable parameters for terrain
vec3 skyColor = vec3(0.5f, 0.7f, 1.0f);     
vec3 groundColor = vec3(0.3f, 0.7f, 0.1f);   

// Material properties
float shininess = 32.0f; 

void main()
{
   
    vec3 norm = normalize(Normal);
    vec3 light = normalize(lightDir);

    // Ambient lighting
    vec3 ambient = ambientColor * Color;

    // Diffuse lighting
    float diffuseStrength = max(dot(norm, light), 0.0);
    vec3 diffuse = diffuseStrength * lightColor * Color;

    // Specular lighting
    vec3 viewDir = normalize(-Pos); // Direction from fragment to camera
    vec3 reflectDir = reflect(-light, norm); // Reflection of light direction
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); // Phong specular reflection
    vec3 specular = spec * lightColor;

    vec3 illumination = ambient + diffuse + specular;

    vec3 finalColor = mix(Color, skyColor, diffuseStrength);

    FragColor = vec4(illumination * finalColor, 1.0);
}