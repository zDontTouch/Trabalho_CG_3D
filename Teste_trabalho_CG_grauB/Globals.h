#pragma once
#include <vector>
#include "Model_object.h"
#include "Scenario.h"

using namespace std;

namespace Globals {

	float MOUSE_SENSIBILITY = 0.2;
	float MOVEMENT_TIC = 0.005;
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

	const int NO_DIFFICULTY = 0;
	const int EASY = 1;
	const int MEDIUM = 2;
	const int HARD = 3;

	int TARGET_PITCH_INACTIVE = 89;
	int TARGET_PITCH_ACTIVE = 0;

	const float INTERACTION_DISTANCE = 3;

	const vector<int> MAX_ROUND_SECONDS_TIME{ 1,0 };
	const int MAX_ROUND_SECONDS_TIME_INTEGER = 10;

	const float BODY_SHOT_SCORE = 100;
	const float HEAD_SHOT_SCORE = 150;
	const int MISSED_SHOT = 0;

	const int MAX_BULLETS_ON_CHAMBER = 15;

	Scenario MAP;

	vector<Model_object> game_elements{

		MAP.map_walls

	};

}