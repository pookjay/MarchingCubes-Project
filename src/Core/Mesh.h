#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "Utility/Shader.h"


class Mesh {

public:
	Mesh();
	~Mesh();

	void ConstructMesh(struct GridPoint grid[], int gridSize);

	void RenderMesh();


private:
	unsigned int VAO, position_VBO, normal_VBO, EBO;
	std::vector<float> vertices;
	std::vector<float> normals;

	Utility::Shader MeshShader;
};