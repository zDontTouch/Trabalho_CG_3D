#pragma once
#include "Model_object.h"
#include "Target.h"
#include "Target_part.h"
#include "Interactive_object.h"
#include <time.h>
#include "Globals.h"

using namespace std;
using namespace Globals;

class Scenario
{
public:

	Model_object map_walls;
	vector<Target> targets_easy;
	vector<Target> targets_medium;
	vector<Interactive_object> control_buttons;

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
		Shape control_table1(vector<Vertex> {Vertex(2, 3, -2), Vertex(-2, 3, -2), Vertex(-2, 0, -2), Vertex(2, 0, -2)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape control_table2(vector<Vertex> {Vertex(2, 3, -3), Vertex(-2, 3, -3), Vertex(-2, 0, -3), Vertex(2, 0, -3)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape control_table3(vector<Vertex> {Vertex(2, 3, -3), Vertex(2, 3, -2), Vertex(2, 0, -2), Vertex(2, 0, -3)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape control_table4(vector<Vertex> {Vertex(-2, 3, -3), Vertex(-2, 3, -2), Vertex(-2, 0, -2), Vertex(-2, 0, -3)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape control_table5(vector<Vertex> {Vertex(2, 3, -2), Vertex(-2, 3, -2), Vertex(-2, 3, -3), Vertex(2, 3, -3)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape medium_target_cover1(vector<Vertex>{Vertex(-2.5, 1, 27), Vertex(-1.0, 1, 27), Vertex(-1.0, 0, 27), Vertex(-2.5, 0, 27)}, vector<float>{0.2f, 0.1f, 0.0f});
		Shape medium_target_cover2(vector<Vertex>{Vertex(-5.5, 1, 23), Vertex(-3.0, 1, 23), Vertex(-3.0, 0, 23), Vertex(-5.5, 0, 23)}, vector<float>{0.2f, 0.1f, 0.0f});
		Shape medium_target_cover3(vector<Vertex>{Vertex(1.5, 1, 23), Vertex(4.0, 1, 23), Vertex(4.0, 0, 23), Vertex(1.5, 0, 23)}, vector<float>{0.2f, 0.1f, 0.0f});
		Shape division4(vector<Vertex>{Vertex(6, 3, 30), Vertex(6, 3, 9), Vertex(6, 0, 9), Vertex(6, 0, 30)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape division5(vector<Vertex>{Vertex(5, 3, 30), Vertex(5, 3, 9), Vertex(5, 0, 9), Vertex(5, 0, 30)}, vector<float>{0.3f, 0.3f, 0.3f});
		Shape division6(vector<Vertex>{Vertex(6, 3, 9), Vertex(5, 3, 9), Vertex(5, 0, 9), Vertex(6, 0, 9)}, vector<float>{0.3f, 0.3f, 0.3f});
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
			difficulty_floor_2,
			control_table1,
			control_table2,
			control_table3,
			control_table4,
			control_table5,
			medium_target_cover1,
			medium_target_cover2,
			medium_target_cover3,
			division4,
			division5,
			division6
		};
		map_walls.shapes = walls;
		//calculating normal vectors
		for (int i = 0; i < map_walls.shapes.size(); i++) {
			map_walls.shapes[i].normal_vector = CalculateVectorNormal(map_walls.shapes[i]);
		}

		//CREATING EASY MODE TARGETS (X BETWEEN -20x-8, Z BETWEEN 11x30)

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

		// CREATING MEDIUM MODE TARGETS

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//body - target 4
		Target_part target4_body(vector <Vertex> {Vertex(-5, 2, 0), Vertex(-4.3, 2, 0), Vertex(-4.3, 0, 0), Vertex(-5, 0, 0)}, vector<float>{1, 1, 1});
		//head - target 4
		Target_part target4_head(vector <Vertex> {Vertex(-4.8, 2.4, 0), Vertex(-4.5, 2.4, 0), Vertex(-4.5, 2, 0), Vertex(-4.8, 2, 0)}, vector<float>{1, 1, 1});
		vector<Shape> target_medium_4_parts{
			target4_head,
			target4_body
		};
		//creating and definig single model object for each complete target
		Target target_medium_4_complete;
		target_medium_4_complete.shapes = target_medium_4_parts;
		target_medium_4_complete.set_translation(0, 0, 25);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//body - target 5
		Target_part target5_body(vector <Vertex> {Vertex(-2, 2, 0), Vertex(-1.3, 2, 0), Vertex(-1.3, 0, 0), Vertex(-2, 0, 0)}, vector<float>{1, 1, 1});
		//head - target 5
		Target_part target5_head(vector <Vertex> {Vertex(-1.8, 2.4, 0), Vertex(-1.5, 2.4, 0), Vertex(-1.5, 2, 0), Vertex(-1.8, 2, 0)}, vector<float>{1, 1, 1});
		vector<Shape> target_medium_5_parts{
			target5_head,
			target5_body
		};
		//creating and definig single model object for each complete target
		Target target_medium_5_complete;
		target_medium_5_complete.shapes = target_medium_5_parts;
		target_medium_5_complete.set_translation(0, 0, 28);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//body - target 6
		Target_part target6_body(vector <Vertex> {Vertex(2.3, 2, 0), Vertex(3, 2, 0), Vertex(3, 0, 0), Vertex(2.3, 0, 0)}, vector<float>{1, 1, 1});
		//head - target 6
		Target_part target6_head(vector <Vertex> {Vertex(2.5, 2.4, 0), Vertex(2.8, 2.4, 0), Vertex(2.8, 2, 0), Vertex(2.5, 2, 0)}, vector<float>{1, 1, 1});
		vector<Shape> target_medium_6_parts{
			target6_head,
			target6_body
		};
		//creating and definig single model object for each complete target
		Target target_medium_6_complete;
		target_medium_6_complete.shapes = target_medium_6_parts;
		target_medium_6_complete.set_translation(0, 0, 24);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		//creating all targets vector
		vector<Target> targets_medium_mode{
			target_medium_4_complete,
			target_medium_5_complete,
			target_medium_6_complete
		};
		targets_medium = targets_medium_mode;
		//calculating normal vectors
		for (int i = 0; i < targets_medium.size(); i++) {
			for (int j = 0; j < targets_medium[i].shapes.size(); j++) {
				targets_medium[i].shapes[j].normal_vector = CalculateVectorNormal(targets_medium[i].shapes[j]);
			}
		}


		// CREATING INTERACTION BUTTONS

		//mouse sensibility decrease button
		Shape control_table_button_sense_minus1(vector<Vertex> {Vertex(-1.8, 2.0, -1.9), Vertex(-1.5, 2.0, -1.9), Vertex(-1.5, 1.5, -1.9), Vertex(-1.8, 1.5, -1.9)}, vector<float>{0.2f, 0.2f, 0.2f});
		vector<Shape> button_sense_minus_shapes{
			control_table_button_sense_minus1
		};
		Interactive_object button_sense_minus;
		button_sense_minus.shapes = button_sense_minus_shapes;
		button_sense_minus.set_action(&MOUSE_SENSIBILITY, SUBTRACT, 0.02);
		button_sense_minus.hud_label = "Decrease mouse sensibility";
		control_buttons.push_back(button_sense_minus);

		//mouse sensibility increase button
		Shape control_table_button_sense_plus1(vector<Vertex> {Vertex(-1.3, 2.0, -1.9), Vertex(-1.0, 2.0, -1.9), Vertex(-1.0, 1.5, -1.9), Vertex(-1.3, 1.5, -1.9)}, vector<float>{0.2f, 0.2f, 0.2f});
		vector<Shape> button_sense_plus_shapes{
			control_table_button_sense_plus1
		};
		Interactive_object button_sense_plus;
		button_sense_plus.shapes = button_sense_plus_shapes;
		button_sense_plus.set_action(&MOUSE_SENSIBILITY, ADD, 0.02);
		button_sense_plus.hud_label = "Increase mouse sensibility";
		control_buttons.push_back(button_sense_plus);

		//round timer decrease button
		Shape control_table_button_timer_minus1(vector<Vertex> {Vertex(-0.8, 2.0, -1.9), Vertex(-0.5, 2.0, -1.9), Vertex(-0.5, 1.5, -1.9), Vertex(-0.8, 1.5, -1.9)}, vector<float>{0.2f, 0.2f, 0.2f});
		vector<Shape> button_timer_minus_shapes{
			control_table_button_timer_minus1
		};
		Interactive_object button_timer_minus;
		button_timer_minus.shapes = button_timer_minus_shapes;
		button_timer_minus.set_action(&MAX_ROUND_SECONDS_TIME, SUBTRACT, 1);
		button_timer_minus.hud_label = "Decrease round time";
		button_timer_minus.is_value_important_to_hud_label = true;
		control_buttons.push_back(button_timer_minus);

		//round timer increase button
		Shape control_table_button_timer_plus1(vector<Vertex> {Vertex(-0.3, 2.0, -1.9), Vertex(0.0, 2.0, -1.9), Vertex(0.0, 1.5, -1.9), Vertex(-0.3, 1.5, -1.9)}, vector<float>{0.2f, 0.2f, 0.2f});
		vector<Shape> button_timer_plus_shapes{
			control_table_button_timer_plus1
		};
		Interactive_object button_timer_plus;
		button_timer_plus.shapes = button_timer_plus_shapes;
		button_timer_plus.set_action(&MAX_ROUND_SECONDS_TIME, ADD, 1);
		button_timer_plus.hud_label = "Increase round time";
		button_timer_plus.is_value_important_to_hud_label = true;
		control_buttons.push_back(button_timer_plus);

		//calculating normal vectors
		for (int i = 0; i < control_buttons.size(); i++) {
			for (int j = 0; j < control_buttons[i].shapes.size(); j++) {
				control_buttons[i].shapes[j].normal_vector = CalculateVectorNormal(control_buttons[i].shapes[j]);
			}
		}

		//since all button interactions will be made with the player looking towards -z axis direction, the interaction buttons' normal vector should be z-inverted
		for (int i = 0; i < control_buttons.size(); i++) {
			control_buttons[i].shapes[0].normal_vector = { control_buttons[i].shapes[0].normal_vector[0], control_buttons[i].shapes[0].normal_vector[1], control_buttons[i].shapes[0].normal_vector[2] * -1 };
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
		for (int i = 0; i < targets_medium.size(); i++) {
			targets_medium[i].draw_model_object();
		}

		for (int i = 0; i < control_buttons.size(); i++) {
			control_buttons[i].draw_model_object();
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

		//draw lines of left-most division
		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(6, 3, 9);
		glVertex3f(6, 0, 9);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(5, 3, 9);
		glVertex3f(5, 0, 9);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(5.99, 0.001, 9);
		glVertex3f(5.99, 0.001, 30);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(5.01, 0.001, 9);
		glVertex3f(5.01, 0.001, 30);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(5.99, 3, 9);
		glVertex3f(5.99, 3, 30);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(5.01, 3, 9);
		glVertex3f(5.01, 3, 30);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(5, 3, 9);
		glVertex3f(6, 3, 9);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(5, 0.01, 9);
		glVertex3f(6, 0.01, 9);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(5.01, 1.0, 9.99);
		glVertex3f(5.01, 0.01, 9.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(5.99, 1.0, 9.99);
		glVertex3f(5.99, 0.01, 9.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(5.01, 1.01, 10);
		glVertex3f(5.01, 1.01, 11);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(5.99, 1.01, 10);
		glVertex3f(5.99, 1.01, 11);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(5.99, 3, 29.99);
		glVertex3f(5.99, 0, 29.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(5.01, 3, 29.99);
		glVertex3f(5.01, 0, 29.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(6.0, 0, 9.99);
		glVertex3f(6.0, 1, 9.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(6.01, 1, 10);
		glVertex3f(6.01, 1, 11);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(5.0, 0, 9.99);
		glVertex3f(5.0, 1, 9.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(4.99, 1, 10);
		glVertex3f(4.99, 1, 11);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(4.99, 0, 9);
		glVertex3f(4.99, 0, 30);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(6.01, 0, 9);
		glVertex3f(6.01, 0, 30);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(6.01, 0, 29.99);
		glVertex3f(6.01, 3, 29.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(4.99, 0, 29.99);
		glVertex3f(4.99, 3, 29.99);
		glEnd();

		//draw lines of the control table
		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-2, 0, -1.99);
		glVertex3f(-2, 3, -1.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(2, 0, -1.99);
		glVertex3f(2, 3, -1.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-2, 0, -3.01);
		glVertex3f(-2, 3, -3.01);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(2, 0, -3.01);
		glVertex3f(2, 3, -3.01);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-2, 3, -3);
		glVertex3f(2, 3, -3);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-2, 3, -2);
		glVertex3f(2, 3, -2);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-2, 3, -2);
		glVertex3f(-2, 3, -3);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(2, 3, -2);
		glVertex3f(2, 3, -3);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-1.99, 0.01, -3);
		glVertex3f(2, 0.01, -3);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-1.99, 0.01, -1.99);
		glVertex3f(2, 0.01, -1.99);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(-1.99, 0.01, -1.99);
		glVertex3f(-1.99, 0.01, -3);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex3f(2, 0.01, -1.99);
		glVertex3f(2, 0.01, -3);
		glEnd();
	}

	int difficulty_selected(float cam_pos_x, float cam_pos_z) {

		//testing easy mode selected (difficulty_floor_1)
		if (cam_pos_x > -20 && cam_pos_x < -8) {
			if (cam_pos_z > 8 && cam_pos_z < 10) {
				return EASY;
			}
		}

		if (cam_pos_x > -7 && cam_pos_x < 5) {
			if (cam_pos_z > 8 && cam_pos_z < 10) {
				return MEDIUM;
			}
		}

		return NO_DIFFICULTY;

	}

	void reload_target_pitches() {

		srand(time(NULL));

		for (int i = 0; i < targets_easy.size(); i++) {
			for (int j = 0; j < targets_easy[i].shapes.size(); j++) {
				targets_easy[i].shapes[j].color = { 1.0f, 1.0f, 1.0f };
			}
			targets_easy[i].pitch = (rand() % 2 == 0) ? TARGET_PITCH_ACTIVE : TARGET_PITCH_INACTIVE;
			if (targets_easy[i].pitch == TARGET_PITCH_ACTIVE) {
				targets_easy[i].is_active = true;
				targets_easy[i].is_dead = false;
			}
			else if (targets_easy[i].pitch == TARGET_PITCH_INACTIVE) {
				targets_easy[i].is_active = false;
				targets_easy[i].is_dead = false;
			}
		}

		for (int i = 0; i < targets_medium.size(); i++) {
			for (int j = 0; j < targets_medium[i].shapes.size(); j++) {
				targets_medium[i].shapes[j].color = { 1.0f, 1.0f, 1.0f };
			}
			targets_medium[i].pitch = (rand() % 2 == 0) ? TARGET_PITCH_ACTIVE : TARGET_PITCH_INACTIVE;
			if (targets_medium[i].pitch == TARGET_PITCH_ACTIVE) {
				targets_medium[i].is_active = true;
				targets_medium[i].is_dead = false;
			}
			else if (targets_medium[i].pitch == TARGET_PITCH_INACTIVE) {
				targets_medium[i].is_active = false;
				targets_medium[i].is_dead = false;
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

