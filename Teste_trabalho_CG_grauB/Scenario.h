#pragma once
#include "Model_object.h"
#include "Target.h"
#include "Target_part.h"
#include <time.h>

using namespace std;

const int LOCAL_NO_DIFFICULTY = 0;
const int LOCAL_EASY = 1;
const int LOCAL_MEDIUM = 2;
const int LOCAL_HARD = 3;

int LOCAL_TARGET_PITCH_INACTIVE = 89;
int LOCAL_TARGET_PITCH_ACTIVE = 0;

class Scenario
{
public:

	Model_object map_walls;
	vector<Target> targets_easy;

	Scenario()
	{
		//creating map solid and fixed elements
		Shape floor(vector <Vertex> {Vertex(-20, 0, 30), Vertex(-20, 0, -20), Vertex(20, 0, -20), Vertex(20, 0, 30)}, vector<float>{0.3f,0.2f,0.1f});
		Shape wall1(vector <Vertex> {Vertex(-20, 4, 30), Vertex(20, 4, 30), Vertex(20, 0, 30), Vertex(-20, 0, 30)}, vector<float>{0.2f, 0.2f, 0.2f});
		Shape wall2(vector <Vertex> {Vertex(20, 4, 30), Vertex(20, 4, -20), Vertex(20, 0, -20), Vertex(20, 0, 30)}, vector<float>{0.2f, 0.2f, 0.2f});
		Shape wall3(vector <Vertex> {Vertex(-20, 4, -20), Vertex(20, 4, -20), Vertex(20, 0, -20), Vertex(-20, 0, -20)}, vector<float>{0.2f, 0.2f, 0.2f});
		Shape wall4(vector <Vertex> {Vertex(-20, 4, 30), Vertex(-20, 4, -20), Vertex(-20, 0, -20), Vertex(-20, 0, 30)}, vector<float>{0.2f, 0.2f, 0.2f});
		Shape bench1(vector<Vertex> {Vertex(-20, 1, 10), Vertex(20, 1, 10), Vertex(20, 0, 10), Vertex(-20, 0, 10)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape bench2(vector<Vertex> {Vertex(-20, 1, 11), Vertex(20, 1, 11), Vertex(20, 0, 11), Vertex(-20, 0, 11)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape bench3(vector<Vertex> {Vertex(-20, 1, 11), Vertex(20, 1, 11), Vertex(20, 1, 10), Vertex(-20, 1, 10)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape division1(vector<Vertex>{Vertex(-7, 3, 30), Vertex(-7, 3, 9), Vertex(-7, 0, 9), Vertex(-7, 0, 30)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape division2(vector<Vertex>{Vertex(-8, 3, 30), Vertex(-8, 3, 9), Vertex(-8, 0, 9), Vertex(-8, 0, 30)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape division3(vector<Vertex>{Vertex(-7, 3, 9), Vertex(-8, 3, 9), Vertex(-8, 0, 9), Vertex(-7, 0, 9)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape difficulty_floor_1(vector<Vertex>{Vertex(-8,0.01,8), Vertex(-20,0.01,8), Vertex(-20,0.01,10), Vertex(-8,0.01,10)}, vector<float>{0, 1, 0});
		Shape difficulty_floor_2(vector<Vertex>{Vertex(5, 0.01, 8), Vertex(-7, 0.01, 8), Vertex(-7, 0.01, 10), Vertex(5, 0.01, 10)}, vector<float>{1, 1, 0});
		vector<Shape> walls{
			floor,
			wall1,
			wall2,
			wall3,
			wall4,
			bench1,
			bench2,
			bench3,
			division1,
			division2,
			division3,
			difficulty_floor_1,
			difficulty_floor_2
		};
		map_walls.shapes = walls;
		//calculating normal vectors
		for (int i = 0; i < map_walls.shapes.size(); i++) {
			map_walls.shapes[i].normal_vector = CalculateVectorNormal(map_walls.shapes[i]);
		}

		//creating easy mode targets (x between -20x-8, z between 11x30)

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		 //body - target 1
		Target_part target1_body(vector <Vertex> {Vertex(-19, 2, 0), Vertex(-18.3, 2, 0), Vertex(-18.3, 0, 0) , Vertex(-19, 0, 0)}, vector<float>{1, 1, 1});
		 //head - target 1
		Target_part target1_head(vector <Vertex> {Vertex(-18.8, 2.4, 0), Vertex(-18.5, 2.4, 0), Vertex(-18.5, 2, 0), Vertex(-18.8, 2, 0)}, vector<float>{1, 1, 1});
		vector<Shape> target_easy_1_parts{
			target1_head,
			target1_body
		};
		//creating and definig single model object for each complete target
		Target target_easy_1_complete;
		target_easy_1_complete.shapes = target_easy_1_parts;
		target_easy_1_complete.set_translation(0, 0, 20);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//body - target 2
		Target_part target2_body(vector <Vertex> {Vertex(-16, 2, 0), Vertex(-15.3, 2, 0), Vertex(-15.3, 0, 0), Vertex(-16, 0, 0)}, vector<float>{1, 1, 1});
		//head - target 2
		Target_part target2_head(vector <Vertex> {Vertex(-15.8, 2.4, 0), Vertex(-15.5, 2.4, 0), Vertex(-15.5, 2, 0), Vertex(-15.8, 2, 0)}, vector<float>{1, 1, 1});
		vector<Shape> target_easy_2_parts{
			target2_head,
			target2_body
		};
		//creating and definig single model object for each complete target
		Target target_easy_2_complete;
		target_easy_2_complete.shapes = target_easy_2_parts;
		target_easy_2_complete.set_translation(0, 0, 25);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//body - target 3
		Target_part target3_body(vector <Vertex> {Vertex(-11, 2, 0), Vertex(-10.3, 2, 0), Vertex(-10.3, 0, 0), Vertex(-11, 0, 0)}, vector<float>{1, 1, 1});
		//head - target 3
		Target_part target3_head(vector <Vertex> {Vertex(-10.8, 2.4, 0), Vertex(-10.5, 2.4, 0), Vertex(-10.5, 2, 0), Vertex(-10.8, 2, 0)}, vector<float>{1, 1, 1});
		vector<Shape> target_easy_3_parts{
			target3_head,
			target3_body
		};
		//creating and definig single model object for each complete target
		Target target_easy_3_complete;
		target_easy_3_complete.shapes = target_easy_3_parts;
		target_easy_3_complete.set_translation(0, 0, 22);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		//creating all targets vector
		vector<Target> targets_easy_mode{
			target_easy_1_complete,
			target_easy_2_complete,
			target_easy_3_complete
		};
		targets_easy = targets_easy_mode;
		//calculating normal vectors
		for (int i = 0; i < targets_easy.size(); i++) {
			for (int j = 0; j < targets_easy[i].shapes.size(); j++) {
				targets_easy[i].shapes[j].normal_vector = CalculateVectorNormal(targets_easy[i].shapes[j]);
			}
		}
	}
	
	void draw_map() {

		//AXIS LINES
		glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(100, 0, 0);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 100, 0);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 100);
		glEnd();

		map_walls.draw_model_object();
		for (int i = 0;i < targets_easy.size();i++) {
			targets_easy[i].draw_model_object();
		}

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

		//draw lines of right-most division
		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-7, 3, 9);
		glVertex3f(-7, 0, 9);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-8, 3, 9);
		glVertex3f(-8, 0, 9);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-6.99, 0.001, 9);
		glVertex3f(-6.99, 0.001, 30);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-8.01, 0.001, 9);
		glVertex3f(-8.01, 0.001, 30);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-6.99, 3, 9);
		glVertex3f(-6.99, 3, 30);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-8.01, 3, 9);
		glVertex3f(-8.01, 3, 30);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-8, 3, 9);
		glVertex3f(-7, 3, 9);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-8, 0.01, 9);
		glVertex3f(-7, 0.01, 9);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-8.01, 1.0, 9.99);
		glVertex3f(-8.01, 0.01, 9.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-6.99, 1.0, 9.99);
		glVertex3f(-6.99, 0.01, 9.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-8.01, 1.01, 10);
		glVertex3f(-8.01, 1.01, 11);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-6.99, 1.01, 10);
		glVertex3f(-6.99, 1.01, 11);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-6.99, 3, 29.99);
		glVertex3f(-6.99, 0, 29.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-8.01, 3, 29.99);
		glVertex3f(-8.01, 0, 29.99);
		glEnd();
	}

	int difficulty_selected(float cam_pos_x, float cam_pos_z) {

		//testing easy mode selected (difficulty_floor_1)
		if (cam_pos_x > -20 && cam_pos_x < -8) {
			if (cam_pos_z > 8 && cam_pos_z < 10) {
				return LOCAL_EASY;
			}
		}

		if (cam_pos_x > -7 && cam_pos_x < 5) {
			if (cam_pos_z > 8 && cam_pos_z < 10) {
				return LOCAL_MEDIUM;
			}
		}

		return LOCAL_NO_DIFFICULTY;

	}

	void reload_target_pitches() {

		srand(time(NULL));

		for (int i = 0; i < targets_easy.size(); i++) {
			for (int j = 0; j < targets_easy[i].shapes.size(); j++) {
				targets_easy[i].shapes[j].color = { 1.0f, 1.0f, 1.0f };
			}
			targets_easy[i].pitch = (rand() % 2 == 0) ? LOCAL_TARGET_PITCH_ACTIVE : LOCAL_TARGET_PITCH_INACTIVE;
			if (targets_easy[i].pitch == LOCAL_TARGET_PITCH_ACTIVE) {
				targets_easy[i].is_active = true;
				targets_easy[i].is_dead = false;
			}
			else if (targets_easy[i].pitch == LOCAL_TARGET_PITCH_INACTIVE) {
				targets_easy[i].is_active = false;
				targets_easy[i].is_dead = false;
			}
		}
	}

	vector<float> CalculateVectorNormal(Shape s) {
		float Qx, Qy, Qz, Px, Py, Pz;

		Qx = s.vertexes[1].pos_x - s.vertexes[0].pos_x;
		Qy = s.vertexes[1].pos_y - s.vertexes[0].pos_y;
		Qz = s.vertexes[1].pos_z - s.vertexes[0].pos_z;

		Px = s.vertexes[2].pos_x - s.vertexes[0].pos_x;
		Py = s.vertexes[2].pos_y - s.vertexes[0].pos_y;
		Pz = s.vertexes[2].pos_z - s.vertexes[0].pos_z;

		float normalX = ((Py*Qz) - (Pz*Qy));
		float normalY = ((Pz*Qx) - (Px*Qz));
		float normalZ = ((Px*Qy) - (Py*Qx));

		//normalizing
		float length = sqrt(normalX*normalX + normalY*normalY + normalZ*normalZ);
		normalX = normalX / length;
		normalY = normalY / length;
		normalZ = normalZ / length;

		return vector<float> {normalX,normalY,normalZ};
	}
};

