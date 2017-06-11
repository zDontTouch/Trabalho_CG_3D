#pragma once
#include "Globals.h"
#include "Coordinates.h"
#include "Point.h"

using namespace Globals;
using namespace std;

class Score_Manager
{
public:

	int current_score;

	int bullets_fired;
	int bullets_on_target;

	int headshots;
	int bodyshots;

	float round_seconds;

	vector<Point> shots_on_target{};

	Score_Manager()
	{
		current_score = 0;
		bullets_fired = 0;
		bullets_on_target = 0;
		headshots = 0;
		bodyshots = 0;
		round_seconds = MAX_ROUND_SECONDS_TIME;
	}

	void score(int score) {
		current_score += score;
		bullets_fired++;

		if (score != MISSED_SHOT)
			bullets_on_target++;

		if (score == HEAD_SHOT_SCORE) 
			headshots++;
		else if (score == BODY_SHOT_SCORE) 
			bodyshots++;

	}

};

