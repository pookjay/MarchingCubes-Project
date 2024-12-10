#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in float type;
layout(location = 2) in vec3 aNormals;

out vec3 Pos;
out vec3 Normal;
out vec3 Color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 perspectiveMatrix;

void main()
{
	mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
	Normal = normalize(normalMatrix * aNormals);

	Pos = aPos;

	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);

	if(type == 0) {
		Color = vec3(0.3f, 0.7f, 0.1f);
	}
	else
	{
		Color = vec3(0.3f, 0.3f, 0.8f);
	}

}
