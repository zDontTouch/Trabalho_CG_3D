#pragma once
#include "Model_object.h"
#include "Globals.h"

using namespace Globals;
using namespace std;

class Interactive_object :
	public Model_object
{
public:

	float *variable;
	int action;
	float value;
	string hud_label;

	Interactive_object()
	{
	}

	void set_action(float *variable, int action, float value) {
		this->variable = variable;
		this->action = action;
		this->value = value;
	}

	void execute_interaction() {

		switch (action)
		{
		case ADD:
			*variable += value;
			break;
		case SUBTRACT:
			if(*variable > (0+value)) //make sure that the variable will never have values <=0 (for example, mouse sensibility)
				*variable -= value;
			break;
		case MULTIPLY:
			*variable *= value;
			break;
		case DIVIDE:
			*variable /= value;
			break;
		}

	}

};

