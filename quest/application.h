#pragma once

#define BOMBS_COUNT 20
#define HEALTH_BOTTLES_COUNT 20
#define FORW_BORDER 1
#define BACK_BORDER 20
#define LEFT_BORDER 1
#define RIGHT_BORDER 20
#define INIT_X int((RIGHT_BORDER - LEFT_BORDER)/2)
#define INIT_Y int((BACK_BORDER - FORW_BORDER)/2)
#define INIT_HEALTH 100
#define BOTTLE_ADD_HEAL_POINTS 25
#define BOMB_REMOVE_HEAL_POINTS 50

#include "position.h"
#include "items.h"
#include "units.h"

class application {

public:

	void run();

};