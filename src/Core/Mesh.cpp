#include "Mesh.h"

#include <vector>
#include <iostream>

#include <glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Core/Application.h"
#include "Core/MarchingCubes.h"


Mesh::Mesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	MeshShader.BuildFiles("shaders/march.vert", "shaders/march.frag");
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::ConstructMesh()
{
}

void Mesh::RenderMesh()
{
	GridCell cell;
	for (int i = 0; i < 8; ++i)
	{
		//cell.val[i] = 1.0f;
	}

	cell.val[0] = 0.0f;
	cell.val[3] = 0.0f;
	cell.val[7] = 0.0f;

	int cubeIndex = CalculateCubeIndex(cell);
	//std::cout << cubeIndex << std::endl;
	//std::cout << edgeTable[cubeIndex] << std::endl;

	Vec3 vertexList[12];

	EdgeIntersection(cubeIndex, cell, vertexList);

	for (int i = 0; i < 12; ++i)
	{
		//std::cout << vertexList[i].x << ", " << vertexList[i].y << ", " << vertexList[i].z << std::endl;
	}

	std::vector<float> vertices;

	//std::cout << vertexList[triTable[cubeIndex][0]].x << ", " << vertexList[triTable[cubeIndex][0]].y << ", " << vertexList[triTable[cubeIndex][0]].z << std::endl;

	for (int i = 0; triTable[cubeIndex][i] != -1; i += 3) {
		vertices.push_back(vertexList[triTable[cubeIndex][i    ]].x);
		vertices.push_back(vertexList[triTable[cubeIndex][i    ]].y);
		vertices.push_back(vertexList[triTable[cubeIndex][i	   ]].z);

		vertices.push_back(vertexList[triTable[cubeIndex][i + 1]].x);
		vertices.push_back(vertexList[triTable[cubeIndex][i + 1]].y);
		vertices.push_back(vertexList[triTable[cubeIndex][i + 1]].z);

		vertices.push_back(vertexList[triTable[cubeIndex][i + 2]].x);
		vertices.push_back(vertexList[triTable[cubeIndex][i + 2]].y);
		vertices.push_back(vertexList[triTable[cubeIndex][i + 2]].z);
	}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	MeshShader.Bind();

	glm::mat4 pos(1.0f);
	pos = glm::translate(pos, glm::vec3(0.0f, 0.0f, -10.0f));

	glUniformMatrix4fv(glGetUniformLocation(MeshShader.GetID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(pos));
	glUniformMatrix4fv(glGetUniformLocation(MeshShader.GetID(), "viewMatrix"), 1, GL_FALSE, glm::value_ptr(camera.viewSpace));
	glUniformMatrix4fv(glGetUniformLocation(MeshShader.GetID(), "perspectiveMatrix"), 1, GL_FALSE, glm::value_ptr(Utility::perspective));

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

	glBindVertexArray(0);
}
