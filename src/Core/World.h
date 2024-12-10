#pragma once
#include "Mesh.h"

#include <glm/glm.hpp>

struct GridPoint {
	glm::vec3 pos;
	double val;
	int type = 0;
};

class World {

public:
	World();

	void GenerateWorld();

	void RegenerateMesh();

	void RenderWorld();

private:

	// Grid 
	static const int gridSize = 128;

	GridPoint grid[gridSize*gridSize*gridSize];

	// Mesh
	Mesh mesh;

};


inline int GetIndex(int x, int y, int z, int gridSize);

float sdBox(glm::vec3 p, glm::vec3 b);
float sdSphere(glm::vec3 pos, float radius);