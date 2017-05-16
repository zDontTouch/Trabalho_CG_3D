#pragma once
#include <math.h>
#include "stdafx.h"
#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include <stdio.h>
#include "Globals.h"
#include "Coordinates.h"
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

		//test scenario bounds
		if (new_x < (MAX_SCENARIO_X-0.3) && new_x > (MIN_SCENARIO_X+0.3)) {
			cam_x = new_x;
		}

		if (new_z < (10-0.3) && new_z > (MIN_SCENARIO_Z+0.3)) {
			cam_z = new_z;
		}

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

			//cout << "posicao da camera: " << cam_x << " x " << cam_y << " x " << cam_z << endl;

	}

	void updateCamera() {
			glTranslatef(-cam_x, -cam_y, -cam_z);

	}

};

