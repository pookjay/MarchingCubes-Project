#include "World.h"

#include <iostream>

#include <External/FastNoiseLite.h>


World::World()
{
	GenerateWorld();

	mesh.ConstructMesh(grid, gridSize);
}

void World::GenerateWorld()
{
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise.SetFrequency(0.03f);
	noise.SetFractalOctaves(5.0f);
	noise.SetFractalLacunarity(2.0f);
	noise.SetFractalGain(0.5f);
	noise.SetFractalType(FastNoiseLite::FractalType_FBm);

	for (int x = 0; x < gridSize; ++x) {
		for (int y = 0; y < gridSize; ++y) {
			for (int z = 0; z < gridSize; ++z) {
				GridPoint point;
				point.pos.x = x; point.pos.y = y; point.pos.z = z;

				//point.val = sdSphere(point.pos - glm::vec3(16, 16, 16), 5.0f);
				//point.val = sdBox(point.pos - glm::vec3(16, 16, 16), glm::vec3(5.0));

				//VoxelData.Density = Position.Z - Height;

				float noiseHeight = noise.GetNoise(float(x), float(y), float(z)) * 25.0f + 5.0f;

				//std::cout << y - noiseHeight << std::endl;
				if (y > noiseHeight) {
					point.val = 1.0f;
				}
				else
				{
					point.val = 0.0f;
				}

				//if(point.val < 0.5)
					//std::cout << sdSphere(point.pos - glm::vec3(16,16,t), 1.0f) << std::endl;

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

float sdBox(glm::vec3 p, glm::vec3 b)
{
	glm::vec3 q = abs(p) - b;
	return glm::length(glm::max(q, glm::vec3(0.0))) + std::min(glm::max(q.x, glm::max(q.y, q.z)), float(0.0));
}