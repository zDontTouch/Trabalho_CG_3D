#pragma once
#include "Shape.h"
class Target_part :
	public Shape
{
public:

	bool already_hit = false;

	using Shape::Shape;

	void hit_target() {
		this->already_hit = true;
	}

};

