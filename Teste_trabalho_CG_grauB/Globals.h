#pragma once
#include <vector>

using namespace std;

namespace Globals {

	float MOUSE_SENSIBILITY = 0.2;
	float MOVEMENT_TIC = 0.005;
	int SCREEN_WIDTH = 1400;
	int SCREEN_HEIGTH = 880;

	float MAX_SCENARIO_X = 20;
	float MIN_SCENARIO_X = -20;
	float MAX_SCENARIO_Z = 30;
	float MIN_SCENARIO_Z = -20;

	bool IS_W_DOWN = false;
	bool IS_S_DOWN = false;
	bool IS_A_DOWN = false;
	bool IS_D_DOWN = false;
	bool IS_CTRL_DOWN = false;
	bool IS_SHIFT_DOWN = false;
	bool IS_TAB_PRESSED = false;

	const int NO_DIFFICULTY = 0;
	const int EASY = 1;
	const int MEDIUM = 2;
	const int HARD = 3;

	float TARGET_PITCH_INACTIVE = 89;
	float TARGET_PITCH_ACTIVE = 0;

	const float INTERACTION_DISTANCE = 3;

	int MAX_ROUND_SECONDS_TIME = 15;

	const float BODY_SHOT_SCORE = 100;
	const float HEAD_SHOT_SCORE = 150;
	const float HOSTAGE_SHOT_SCORE = -75;
	const float MISSED_SHOT = 0;

	const float MAX_BULLETS_ON_CHAMBER = 15;

	enum interaction_actions {
		ADD,
		SUBTRACT,
		MULTIPLY,
		DIVIDE
	};



}