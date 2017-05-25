#pragma once
#include "Model_object.h"
#include "Globals.h"

using namespace std;

class Target :
	public Model_object
{
public:

	int LOCAL_TARGET_PITCH_INACTIVE = 89;
	int LOCAL_TARGET_PITCH_ACTIVE = 0;

	bool is_active;
	bool is_dead;

	Target()
	{
		if (this->pitch == LOCAL_TARGET_PITCH_ACTIVE) {
			is_active = true;
		}
	}

};

