#pragma once
#include <vector>
#include "Vertex.h"
#include "stdafx.h"
#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include <stdio.h>
#include "Globals.h"
#include "Shape.h"

class Model_object
{
public:

	vector<Shape> shapes{};
	float yaw;
	float pitch;

	Model_object()
	{
	}

	void draw_model_object() {

		glPushMatrix();
		for (int i = 0; i < shapes.size(); i++) {
			shapes[i].draw_shape();
		}
		glRotatef(pitch, 1.0, 0.0, 0.0);
		glRotatef(yaw, 0.0, 1.0, 0.0);
		glPopMatrix();
	}

};

