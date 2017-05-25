#pragma once
#include <math.h>
#include "stdafx.h"
#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include <stdio.h>
#include "Globals.h"
#include "Coordinates.h"
#include "Score_Manager.h"
#ifndef PI
#define PI 3.1415926535 
#endif

using namespace std;
using namespace Globals;
using namespace Coordinates;

class Camera_System
{
public:

	float cam_x = 0.0;
	float cam_y = 2.0;
	float cam_z = 0.0;

	vector<float> camera_direction{0,0,0};

	float cam_yaw = 0.0;
	float cam_pitch = 0.0;

	bool is_mouse_in = false;

	Camera_System()
	{
		cam_yaw = 15.0;
		cam_pitch = 6.0;
	}

	void lockCamera() {

		if (cam_pitch > 90) {
			cam_pitch = 90;
		}
		else {
			if (cam_pitch < -90) {
				cam_pitch = -90;
			}
		}

		if (cam_yaw < 0.0) {
			cam_yaw += 360;
		}
		else {
			if (cam_yaw > 360) {
				cam_yaw -= 360;
			}
		}

	}

	void moveCamera(float direction) {

		float new_x = cam_x;
		float new_z = cam_z;

		float rad = (cam_yaw + direction) * PI / 180.0;   //transform to radians

		new_x -= sin(rad) * MOVEMENT_TIC;
		new_z -= cos(rad) * MOVEMENT_TIC;

		//test scenario bounds and bench
		//if (new_x < (MAX_SCENARIO_X-0.3) && new_x > (MIN_SCENARIO_X+0.3)) {
			cam_x = new_x;
		//}

		//if (new_z < (10-0.3) && new_z > (MIN_SCENARIO_Z+0.3)) {
			cam_z = new_z;
		//}

		//test bench divisions

	}

	void moveCameraUp(float distance, float direction) {

		float rad = (cam_pitch + direction) * PI / 180.0;   //transform to radians
		cam_y += sin(rad) * distance;

	}

	void control(float current_mouse_position_x, float current_mouse_position_y, bool is_only_refresh) {
		if (!is_only_refresh) {
			if (is_mouse_in) {
				int screen_middle_horizontal = SCREEN_WIDTH / 2;
				int screen_middle_vertical = SCREEN_HEIGTH / 2;
				glutSetCursor(GLUT_CURSOR_NONE);

				cam_yaw = MOUSE_SENSIBILITY * (screen_middle_horizontal - current_mouse_position_x);
				cam_pitch = MOUSE_SENSIBILITY * (screen_middle_vertical - current_mouse_position_y);
				lockCamera();


				glutWarpPointer(screen_middle_horizontal, screen_middle_vertical);

				if (IS_W_DOWN) {
					moveCamera(FORWARD);
				}

				if (IS_S_DOWN) {
					moveCamera(BACKWARD);
				}

				if (IS_A_DOWN) {
					moveCamera(LEFT);
				}

				if (IS_D_DOWN) {
					moveCamera(RIGHT);
				}

			}
			else {
				glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			}
		}

			glRotatef(-cam_pitch, 1.0, 0.0, 0.0);
			glRotatef(-cam_yaw, 0.0, 1.0, 0.0);

			camera_direction[0] = -(sin(cam_yaw * PI / 180.0));
			camera_direction[1] = - (sin(cam_pitch* PI / 180.0) * cos(cam_yaw* PI / 180.0));
			camera_direction[2] = -(cos(cam_pitch* PI / 180.0) * cos(cam_yaw* PI / 180.0));

	}

	void updateCamera() {
			glTranslatef(-cam_x, -cam_y, -cam_z);

	}

	bool is_camera_aiming_at(Shape s, Model_object parent, Score_Manager current_score) {
		//n - normal plane vector
		//c - point on the plane
		//x0 - point of the beggining of the ray
		//x1 - point of the end of the ray

		vector<float> n = s.normal_vector;
		vector<float> c { s.vertexes[0].pos_x + parent.translateX,s.vertexes[0].pos_y+parent.translateY,s.vertexes[0].pos_z+parent.translateZ };
		vector<float> x0{ cam_x,cam_y,cam_z };
		vector<float> x1{ (cam_x + camera_direction[0] * 50),(cam_y + camera_direction[1] * 50),(cam_z + camera_direction[2] * 50) };

		vector<float> v{ x1[0] - x0[0], x1[1] - x0[1], x1[2] - x0[2] };
		vector<float> w{ c[0] - x0[0], c[1] - x0[1], c[2] - x0[2] };

		// w dot n / v dot n
		float k = (w[0]*n[0] + w[1]*n[1] + w[2]*n[2]) / (v[0]*n[0] + v[1]*n[1] + v[2]*n[2]);

		vector<float> intersection {x0[0] + k * v[0], x0[1] + k * v[1], x0[2] + k * v[2] };

		//TO BE CONTINUED
		if (intersection[0] >= s.vertexes[0].pos_x && intersection[0] <= s.vertexes[1].pos_x) {
			if (intersection[1] >= s.vertexes[2].pos_y && intersection[1] <= s.vertexes[0].pos_y) {
				if (k >= 0) {
					current_score.shots_on_target.push_back(Point(intersection[0],intersection[1],intersection[2]));
					return true;
				}
			}
		}

		return false;

	}

	bool is_camera_aiming_at_shape_for_interaction(Shape s, Model_object parent) {
		//n - normal plane vector
		//c - point on the plane
		//x0 - point of the beggining of the ray
		//x1 - point of the end of the ray

		bool ray_is_intercepting;

		vector<float> n = s.normal_vector;
		vector<float> c{ s.vertexes[0].pos_x + parent.translateX,s.vertexes[0].pos_y + parent.translateY,s.vertexes[0].pos_z + parent.translateZ };
		vector<float> x0{ cam_x,cam_y,cam_z };
		vector<float> x1{ (cam_x + camera_direction[0] * INTERACTION_DISTANCE),(cam_y + camera_direction[1] * INTERACTION_DISTANCE),(cam_z + camera_direction[2] * INTERACTION_DISTANCE) };

		vector<float> v{ x1[0] - x0[0], x1[1] - x0[1], x1[2] - x0[2] };
		vector<float> w{ c[0] - x0[0], c[1] - x0[1], c[2] - x0[2] };

		// w dot n / v dot n
		float k = (w[0] * n[0] + w[1] * n[1] + w[2] * n[2]) / (v[0] * n[0] + v[1] * n[1] + v[2] * n[2]);

		vector<float> intersection{ x0[0] + k * v[0], x0[1] + k * v[1], x0[2] + k * v[2] };

		if (intersection[0] >= s.vertexes[0].pos_x && intersection[0] <= s.vertexes[1].pos_x) {
			if (intersection[1] >= s.vertexes[2].pos_y && intersection[1] <= s.vertexes[0].pos_y) {
				if (k >= 0) {
					//calculating interaction distance
					float distance = (sqrt(pow(cam_x - (s.vertexes[0].pos_x + parent.translateX),2))) + (sqrt(pow(cam_z - (s.vertexes[0].pos_z + parent.translateZ), 2)));
					if (distance <= INTERACTION_DISTANCE)
						return true;
				}
			}
		}

		return false;

	}

};

