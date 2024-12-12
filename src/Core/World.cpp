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
	noise.SetFrequency(0.015f);
	noise.SetFractalOctaves(3.0f);
	noise.SetFractalLacunarity(2.0f);
	noise.SetFractalGain(0.5f);
	noise.SetFractalType(FastNoiseLite::FractalType_FBm);

	for (int x = 0; x < gridSize; ++x) {
		for (int y = 0; y < gridSize; ++y) {
			for (int z = 0; z < gridSize; ++z) {
				GridPoint point;
				point.pos.x = x; point.pos.y = y; point.pos.z = z;

				//point.val = sdBox(point.pos - glm::vec3(16, 16, 16), glm::vec3(5.0));

				float noiseHeight = noise.GetNoise(float(x), float(y), float(z)) * 60.0f + 40.0f;

				// Density
				point.val = y - noiseHeight;

				//if (y < 10) {
				//	point.type = 1;
				//}

				// Assign colors based on height
				glm::vec3 yellow(0.3f, 0.7f, 0.1f);
				glm::vec3 brown(0.45f, 0.29f, 0.07f);
				glm::vec3 white(0.8f, 0.8f, 0.8f);
				
				if (y < 7) {
					point.color = yellow;
				}
				else if (y >= 7 && y < 64) {
					float t = (y - 1) / 25.0f; // Normalize y within the range [3, 12]
					//point.color = Lerp(yellow, brown, t);
					point.color = brown;
				}
				else {
					float t = (y - 64) / 2.0f; // Normalize y within the range [12, 20]
					point.color = Lerp(brown, white, t);
				}

				//if(point.val < 0.5)
					//std::cout << sdSphere(point.pos - glm::vec3(16,16,t), 1.0f) << std::endl;

				float s = sdSphere(point.pos - glm::vec3(128/2, 128/2, 128/2), 20.0f);
				if (s < point.val)
				{
					//point.val = s;
				}

				grid[GetIndex(x, y, z, gridSize)] = point;
			}
		}

	}
}

void World::RegenerateMesh()
{
	mesh.ConstructMesh(grid, gridSize);
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

glm::vec3 Lerp(const glm::vec3& a, const glm::vec3& b, float t) {
	return a + t * (b - a);
}