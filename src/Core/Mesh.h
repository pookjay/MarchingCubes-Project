#pragma once

#include <vector>

#include "Utility/Shader.h"

class Mesh {

public:
	Mesh();
	~Mesh();

	void ConstructMesh(struct GridPoint grid[], int gridSize);

	void RenderMesh();

private:
	unsigned int VAO, VBO, EBO;
	std::vector<float> vertices;

	Utility::Shader MeshShader;
};