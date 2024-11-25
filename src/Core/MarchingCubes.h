#pragma once

#include <cmath>
#include <vector>

#include <glm/glm.hpp>

#include <Core/World.h>

int CalculateCubeIndex(GridPoint cube[8]);

void EdgeIntersection(int cubeIndex, GridPoint cell[8], glm::vec3 vertexList[12]);

// Linearly interpolates
glm::vec3 VertexInterp(double isolevel, glm::vec3 p1, glm::vec3 p2, double valp1, double valp2);

//@brief Builds vertices for the cube
//@param cube is the 8 points needed to march the cube
//@param vertices vector is where the triangle points will be placed
void MarchCube(GridPoint cube[8], std::vector<float>& vertices);


extern int edgeTable[256];

extern int triTable[256][16];