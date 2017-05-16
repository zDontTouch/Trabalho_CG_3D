#pragma once
#include <vector>
#include "Vertex.h"
#include "stdafx.h"
#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include <stdio.h>
#include "Globals.h"
#include "Vertex.h"

using namespace std;

class Shape
{
public:

	vector<Vertex> vertexes;
	vector<float> color;

	Shape(vector<Vertex> shape_vertexes, vector<float> color) {
		vertexes = shape_vertexes;
		this->color = color;
	}

	void draw_shape() {
		
		glBegin(GL_POLYGON);
		glColor3f(color[0], color[1], color[2]);
		for (int i = 0; i < vertexes.size(); i++) {
			glVertex3f(vertexes[i].pos_x, vertexes[i].pos_y, vertexes[i].pos_z);
		}
		glEnd();

	}

};

