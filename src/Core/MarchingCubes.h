#pragma once

#include <cmath>

#include <Core/World.h>

int CalculateCubeIndex(GridCell cube);

void EdgeIntersection(int cubeIndex, GridCell& cell, Vec3 vertexList[12]);

// Linearly interpolates
Vec3 VertexInterp(double isolevel, Vec3 p1, Vec3 p2, double valp1, double valp2);


extern int edgeTable[256];

extern int triTable[256][16];