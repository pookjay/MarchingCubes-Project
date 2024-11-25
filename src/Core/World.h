#pragma once
#include "Mesh.h"

#include <glm/glm.hpp>

struct GridPoint {
	glm::vec3 pos;
	double val;
};

class World {

public:
	World();

	void GenerateWorld();

	void RenderWorld();

private:

	// Grid 
	static const int gridSize = 32;

	GridPoint grid[gridSize*gridSize*gridSize];

	// Mesh
	Mesh mesh;

};


inline int GetIndex(int x, int y, int z, int gridSize);

float sdSphere(glm::vec3 pos, float radius);