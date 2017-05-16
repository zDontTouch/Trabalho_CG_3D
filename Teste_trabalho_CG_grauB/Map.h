#pragma once
#include "Model_object.h"
class Map
{
public:

	Model_object map_walls;

	Map()
	{
		Shape floor(vector <Vertex> {Vertex(-20, 0, 30), Vertex(-20, 0, -20), Vertex(20, 0, -20), Vertex(20, 0, 30)}, vector<float>{0.3f,0.2f,0.1f});
		Shape wall1(vector <Vertex> {Vertex(-20, 4, 30), Vertex(20, 4, 30), Vertex(20, 0, 30), Vertex(-20, 0, 30)}, vector<float>{0.2f, 0.2f, 0.2f});
		Shape wall2(vector <Vertex> {Vertex(20, 4, 30), Vertex(20, 4, -20), Vertex(20, 0, -20), Vertex(20, 0, 30)}, vector<float>{0.2f, 0.2f, 0.2f});
		Shape wall3(vector <Vertex> {Vertex(-20, 4, -20), Vertex(20, 4, -20), Vertex(20, 0, -20), Vertex(-20, 0, -20)}, vector<float>{0.2f, 0.2f, 0.2f});
		Shape wall4(vector <Vertex> {Vertex(-20, 4, 30), Vertex(-20, 4, -20), Vertex(-20, 0, -20), Vertex(-20, 0, 30)}, vector<float>{0.2f, 0.2f, 0.2f});
		Shape bench1(vector<Vertex> {Vertex(-20, 1.4, 10), Vertex(20, 1.4, 10), Vertex(20, 0, 10), Vertex(-20, 0, 10)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape bench2(vector<Vertex> {Vertex(-20, 1.4, 11), Vertex(20, 1.4, 11), Vertex(20, 0, 11), Vertex(-20, 0, 11)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape bench3(vector<Vertex> {Vertex(-20, 1.4, 11), Vertex(20, 1.4, 11), Vertex(20, 1.4, 10), Vertex(-20, 1.4, 10)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape division1(vector<Vertex>{Vertex(-7, 3, 10.5), Vertex(-7, 3, 9.5), Vertex(-7, 0, 9.5), Vertex(-7.0, 0, 10.5)}, vector<float>{0.3f, 0.3f, 0.3f});
		vector<Shape> walls{
			floor,
			wall1,
			wall2,
			wall3,
			wall4,
			bench1,
			bench2,
			bench3,
			division1
		};

		map_walls.shapes = walls;
	}
	
	void draw_map() {

		map_walls.draw_model_object();

		//draw lines between walls
		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(19.99, 4, 29.99);
		glVertex3f(19.99, 0, 29.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(19.99, 4, -19.99);
		glVertex3f(19.99, 0, -19.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-19.99, 4, 29.99);
		glVertex3f(-19.99, 0, 29.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-19.99, 4, -19.99);
		glVertex3f(-19.99, 0, -19.99);
		glEnd();

		//draw lines of the bench
		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-20, 1.0, 11);
		glVertex3f(20, 1.0, 11);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-20, 1.0, 10);
		glVertex3f(20, 1.0, 10);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-20, 1.0, 11);
		glVertex3f(20, 1.0, 11);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-20, 0.01, 9.99);
		glVertex3f(20, 0.01, 9.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-19.99, 1.0, 9.99);
		glVertex3f(-19.99, 0.01, 9.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(19.99, 1.0, 9.99);
		glVertex3f(19.99, 0.01, 9.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(19.99, 1.01, 10);
		glVertex3f(19.99, 1.01, 11);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-19.99, 1.01, 10);
		glVertex3f(-19.99, 1.01, 11);
		glEnd();

		//draw lines between ground and walls
		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-20, 0.005, 29.99);
		glVertex3f(20, 0.005, 29.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-20, 0.005, -19.99);
		glVertex3f(20, 0.005, -19.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-19.99, 0.005, -20);
		glVertex3f(-19.99, 0.005, 30);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(19.99, 0.005, -20);
		glVertex3f(19.99, 0.005, 30);
		glEnd();

	}

};

