#pragma once
#include <string.h>
#include <sstream>

using namespace std;

class Timer
{
public:

	string timer = "";
	int minutes[2];
	int seconds[2];
	int centiseconds[2];

	Timer()
	{
		minutes[0] = 0;
		minutes[1] = 0;
		seconds[0] = 0;
		seconds[1] = 0;
		centiseconds[0] = 0;
		centiseconds[1] = 0;
	}

	void updateTimer() {

		centiseconds[1]++;
		if (centiseconds[1] == 10) {
			centiseconds[1] = 0;
			centiseconds[0]++;
		}

		if (centiseconds[0] == 10) {
			centiseconds[0] = 0;
			seconds[1]++;
		}

		if (seconds[1] == 10) {
			seconds[1] = 0;
			seconds[0]++;
		}

		if (seconds[0] == 6) {
			seconds[0] = 0;
			minutes[1]++;
		}

		if (minutes[1] == 10) {
			minutes[1] = 0;
			minutes[0] ++;
		}

		ostringstream convert;
		timer = "";

		convert.str("");
		convert << minutes[0];
		timer.append(convert.str());

		convert.str("");
		convert << minutes[1];
		timer.append(convert.str());

		timer.append(":");

		convert.str("");
		convert << seconds[0];
		timer.append(convert.str());

		convert.str("");
		convert << seconds[1];
		timer.append(convert.str());

		timer.append(":");

		convert.str("");
		convert << centiseconds[0];
		timer.append(convert.str());

		convert.str("");
		convert << centiseconds[1];
		timer.append(convert.str());

	}

};

