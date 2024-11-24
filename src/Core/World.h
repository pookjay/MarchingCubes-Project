#pragma once

struct Vec3 {
	float x,y,z;
};

struct GridCell {
	Vec3 pos[8] = { 
		{0, 0, 0}, 
		{1, 0, 0},
		{1, 1, 0}, 
		{0, 1, 0}, 
		{0, 0, 1}, 
		{1, 0, 1}, 
		{1, 1, 1}, 
		{0, 1, 1}  
	};
	double val[8];

	GridCell() {
		for (int i = 0; i < 8; ++i) {
			val[i] = 1.0f;
		}
	}
};

class World {

	

};

