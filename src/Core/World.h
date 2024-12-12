#pragma once
#include "Mesh.h"

#include <glm/glm.hpp>

struct GridPoint {
	glm::vec3 pos;
	double val;
	glm::vec3 color;
};

class World {

public:
	World();

	void GenerateWorld();

	void RegenerateMesh();

	void RenderWorld();

	Mesh mesh;
	

private:

	// Grid 
	static const int gridSize = 256;

	GridPoint grid[gridSize*gridSize*gridSize];

	// Mesh

};


inline int GetIndex(int x, int y, int z, int gridSize);

float sdBox(glm::vec3 p, glm::vec3 b);
float sdSphere(glm::vec3 pos, float radius);

glm::vec3 Lerp(const glm::vec3& a, const glm::vec3& b, float t);