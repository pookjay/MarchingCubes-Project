#pragma once

#include "Utility/Shader.h"

class Mesh {

public:
	Mesh();
	~Mesh();

	void ConstructMesh();

	void RenderMesh();

private:
	unsigned int VAO, VBO, EBO;

	Utility::Shader MeshShader;
};