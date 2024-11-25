#include "World.h"

#include <iostream>
#include <random>

World::World()
{
	GenerateWorld();

	mesh.ConstructMesh(grid, gridSize);
}

void World::GenerateWorld()
{
	std::random_device rd; 
	std::mt19937 gen(rd());

	std::uniform_real_distribution<> dis(0.0, 1.0);


	for (int x = 0; x < gridSize; ++x) {
		for (int y = 0; y < gridSize; ++y) {
			for (int z = 0; z < gridSize; ++z) {
				GridPoint point;
				point.pos.x = x; point.pos.y = y; point.pos.z = z;

				point.val = sdSphere(point.pos - glm::vec3(16, 16, 16), 5.0f);

				if(point.val < 0.5)
					std::cout << sdSphere(point.pos - glm::vec3(16,16,16), 1.0f) << std::endl;

				grid[GetIndex(x, y, z, gridSize)] = point;
			}
		}

	}
}

void World::RenderWorld()
{
	mesh.RenderMesh();
}

inline int GetIndex(int x, int y, int z, int gridSize)
{
	return x + gridSize * (z + gridSize * y);
}

float sdSphere(glm::vec3 pos, float radius)
{
	return glm::length(pos) - radius;
}