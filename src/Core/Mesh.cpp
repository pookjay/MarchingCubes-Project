#include "Mesh.h"

#include <vector>

#include <glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Core/Application.h"


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
	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
	};

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	MeshShader.Bind();

	glm::mat4 pos(1.0f);
	pos = glm::translate(pos, glm::vec3(0.0f, 0.0f, -100.0f));

	glUniformMatrix4fv(glGetUniformLocation(MeshShader.GetID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(pos));
	glUniformMatrix4fv(glGetUniformLocation(MeshShader.GetID(), "viewMatrix"), 1, GL_FALSE, glm::value_ptr(camera.viewSpace));
	glUniformMatrix4fv(glGetUniformLocation(MeshShader.GetID(), "perspectiveMatrix"), 1, GL_FALSE, glm::value_ptr(Utility::perspective));

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

	glBindVertexArray(0);
}
