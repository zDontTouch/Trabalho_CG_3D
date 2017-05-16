#pragma once
#include <vector>
#include "Model_object.h"
#include "Map.h"

using namespace std;

namespace Globals {

	float MOUSE_SENSIBILITY = 0.2;
	float MOVEMENT_TIC = 0.002;
	int SCREEN_WIDTH = 1400;
	int SCREEN_HEIGTH = 880;

	int MAX_SCENARIO_X = 20;
	int MIN_SCENARIO_X = -20;
	int MAX_SCENARIO_Z = 30;
	int MIN_SCENARIO_Z = -20;

	bool IS_W_DOWN = false;
	bool IS_S_DOWN = false;
	bool IS_A_DOWN = false;
	bool IS_D_DOWN = false;
	bool IS_CTRL_DOWN = false;
	bool IS_SHIFT_DOWN = false;

	Map MAP;

	vector<Model_object> game_elements{

		MAP.map_walls

	};

}