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

	glm::vec3 lightPos = glm::vec3(0, 0, 0);

private:
	unsigned int VAO, position_VBO, normal_VBO, EBO;
	std::vector<float> vertices;
	std::vector<float> normals;

	int vertexSize = 0;

	Utility::Shader MeshShader;

};


extern int GetIndex(int x, int y, int z, int gridSize);