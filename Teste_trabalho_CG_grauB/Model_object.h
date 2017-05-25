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

	float translateX;
	float translateY;
	float translateZ;

	Model_object()
	{
	}

	void draw_model_object() {

		glPushMatrix();
		glTranslatef(translateX, translateY, translateZ);
		glRotatef(pitch, 1.0, 0.0, 0.0);
		glRotatef(yaw, 0.0, 1.0, 0.0);
		for (int i = 0; i < shapes.size(); i++) {
			shapes[i].draw_shape();
		}
		glPopMatrix();
	}

	void set_translation(float x, float y, float z) {
		this->translateX = x;
		this->translateY = y;
		this->translateZ = z;
	}

};

