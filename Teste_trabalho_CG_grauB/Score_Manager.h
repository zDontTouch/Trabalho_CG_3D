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

	float score_per_second;

	vector<Point> shots_on_target{};

	Score_Manager()
	{
		bullets_fired = 0;
		bullets_on_target = 0;
		headshots = 0;
		bodyshots = 0;
		score_per_second = 0;
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

		score_per_second = current_score / MAX_ROUND_SECONDS_TIME;

	}

};

