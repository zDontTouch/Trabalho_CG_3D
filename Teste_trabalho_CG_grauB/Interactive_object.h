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
	int *variable_integer;
	int action;
	float value;
	string hud_label;
	bool is_value_important_to_hud_label = false;

	Interactive_object()
	{
		variable = NULL;
		variable_integer = NULL;
	}

	void set_action(float *variable, int action, float value) {
		this->variable = variable;
		this->action = action;
		this->value = value;
	}

	void set_action(int *variable, int action, float value) {
		this->variable_integer = variable;
		this->action = action;
		this->value = value;
	}

	void execute_interaction() {

		switch (action)
		{
		case ADD:
			if (variable != NULL)
				*variable += value;
			else
				*variable_integer += value;
			break;
		case SUBTRACT:
			if (variable != NULL)
				*variable -= value;
			else
				*variable_integer -= value;
			break;
		case MULTIPLY:
			if (variable != NULL)
				*variable *= value;
			else
				*variable_integer *= value;
			break;
		case DIVIDE:
			if (variable != NULL)
				*variable /= value;
			else
				*variable_integer /= value;
			break;
		}

	}

	string get_hud_label() {
		
		string ret = "";
		if (is_value_important_to_hud_label) {
			ret.append(this->hud_label);
			ret.append(" (");
			
			ostringstream convert;
			convert.str("");
			if (variable != NULL)
				convert << *variable;
			else
				convert << *variable_integer;
			ret.append(convert.str());

			ret.append(")");
		}
		else {
			ret = this->hud_label;
		}

		return ret;
	}

};

