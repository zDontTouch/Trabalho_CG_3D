#pragma once
#include "Scenario.h"
#include "Model_object.h"

using namespace std;


namespace Global_instances {

	Scenario MAP;

	vector<Model_object> game_elements{

		MAP.map_walls

	};

}

