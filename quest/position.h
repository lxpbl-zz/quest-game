#pragma once

#include "application.h"

#include <cmath>

enum dir { FORW, BACK, LEFT, RIGHT };

struct position {

	int x;
	int y;
	position() {
		x = y = 0;
	}
	position(int x, int y) {
		this->x = x;
		this->y = y;
	}

	bool operator ==(position other) {
		return x == other.x && y == other.y;
	}
	double distance_to(position& other) {
		return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
	}

};