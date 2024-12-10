#include "Mesh.h"

#include <iostream>

#include <glew.h>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Core/Application.h"
#include "Core/World.h"
#include "Core/MarchingCubes.h"


Mesh::Mesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &position_VBO);
	glGenBuffers(1, &normal_VBO);
	glGenBuffers(1, &EBO);

	MeshShader.BuildFiles("shaders/march.vert", "shaders/march.frag");
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &position_VBO);
	glDeleteBuffers(1, &normal_VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::ConstructMesh(GridPoint grid[], int gridSize)
{
	vertexSize = 0;

	for (int x = 0; x < gridSize - 1; ++x) {
		for (int y = 0; y < gridSize - 1; ++y) {
			for (int z = 0; z < gridSize - 1; ++z) {
				GridPoint cube[8];
				cube[0] = grid[GetIndex(x, y, z, gridSize)];
				cube[1] = grid[GetIndex(x + 1, y, z, gridSize)];
				cube[2] = grid[GetIndex(x + 1, y, z + 1, gridSize)];
				cube[3] = grid[GetIndex(x, y, z + 1, gridSize)];
				cube[4] = grid[GetIndex(x, y + 1, z, gridSize)];
				cube[5] = grid[GetIndex(x + 1, y + 1, z, gridSize)];
				cube[6] = grid[GetIndex(x + 1, y + 1, z + 1, gridSize)];
				cube[7] = grid[GetIndex(x, y + 1, z + 1, gridSize)];

				MarchCube(cube, vertices, normals);
			}
		}
	}

	//std::cout << vertices.size() << ", " << normals.size() << std::endl;
	vertexSize = vertices.size();

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, position_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, normal_VBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);

	vertices.clear();
	normals.clear();
}

void Mesh::RenderMesh()
{
	glBindVertexArray(VAO);

	MeshShader.Bind();

	glm::mat4 pos(1.0f);
	pos = glm::translate(pos, glm::vec3(0.0f, 0.0f, -10.0f));

	glUniformMatrix4fv(glGetUniformLocation(MeshShader.GetID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(pos));
	glUniformMatrix4fv(glGetUniformLocation(MeshShader.GetID(), "viewMatrix"), 1, GL_FALSE, glm::value_ptr(camera.viewSpace));
	glUniformMatrix4fv(glGetUniformLocation(MeshShader.GetID(), "perspectiveMatrix"), 1, GL_FALSE, glm::value_ptr(Utility::perspective));

	glDrawArrays(GL_TRIANGLES, 0, vertexSize / 3);

	glBindVertexArray(0);
}
