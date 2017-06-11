#include "stdafx.h"
#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include <stdio.h>
#include "Globals.h"
#include "Timer.h"
#include "Scenario.h"
#include "Score_Manager.h"
#include "Camera_System.h"
#include "Global_instances.h"

using namespace std;
using namespace Globals;
using namespace Global_instances;

Interactive_object DUMMY_INTERACTION;

float angle = 0;

bool is_only_refresh = false;
bool is_time_running = false;
bool is_game_active = false;

bool is_player_on_difficulty_floor = false;

int previous_mouse_pos_x = 0;
int previous_mouse_pos_y = 0;
int mouse_pos_x = 0;
int mouse_pos_y = 0;

int last_score = MISSED_SHOT;

int bullets_on_chamber = MAX_BULLETS_ON_CHAMBER;
bool is_reloading = false;
bool warning_no_bullets = false;
bool score_hit = false;

Interactive_object current_interaction_object;

Timer timer;

Camera_System cam;

vector<Score_Manager> scoreBoards{};

int round_selected = 0;

void print_scoreboard() {

	ostringstream convert;

	//individual round scoreBoard round selection
	string individual_control_label = "[<-] previous round                - "; 
	convert.str("");
	if (round_selected > 0) {
		convert << round_selected;
		individual_control_label.append(convert.str());
	}
	individual_control_label.append(" -                        next round[->]");
	glColor4ub(0, 0, 0, 255);
	glRasterPos3f(2, -15, 0.0);
	for (char& c : individual_control_label)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

	//individual round scoreBoards
	string individual_score_label = "Individual ScoreBoard";
	glColor4ub(0, 0, 0, 255);
	glRasterPos3f(2, 12, 0.0);
	for (char& c : individual_score_label)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

	//total score per second
	string score_per_second_label = "Total score per second: ";
	float round_score = 0;
	int total_seconds = 0;
	for (int i = 0; i < scoreBoards.size(); i++) {
		total_seconds += scoreBoards[i].round_seconds;
		round_score += scoreBoards[i].current_score;
	}
	float score_per_second = (scoreBoards.size()>0)? round_score / total_seconds : 0;
	convert.str("");
	convert << score_per_second;
	score_per_second_label.append(convert.str());
	score_per_second_label.append(" pts.");
	glColor4ub(0, 0, 0, 255);
	glRasterPos3f(-19, -10, 0.0);
	for (char& c : score_per_second_label)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

	//total balance
	string total_score_label = "Total score balance: ";
	int total_score = 0;
	for (int i = 0; i < scoreBoards.size(); i++) {
		total_score += scoreBoards[i].current_score;
	}
	convert.str("");
	convert << total_score;
	total_score_label.append(convert.str());
	total_score_label.append(" pts.");
	glColor4ub(0, 0, 0, 255);
	glRasterPos3f(-19, -8, 0.0);
	for (char& c : total_score_label)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

	//total positive score
	string total_positive_score_label = "Total positive score gathered: ";
	int total_headshots = 0;
	int total_bodyshots = 0;
	int total_positive_score = 0;
	for (int i = 0; i < scoreBoards.size(); i++) {
		total_headshots += scoreBoards[i].headshots;
		total_bodyshots += scoreBoards[i].bodyshots;
	}
	total_positive_score = (total_bodyshots * BODY_SHOT_SCORE) + (total_headshots * HEAD_SHOT_SCORE);
	convert.str("");
	convert << total_positive_score;
	total_positive_score_label.append(convert.str());
	total_positive_score_label.append(" pts.");
	glColor4ub(0, 0, 0, 255);
	glRasterPos3f(-19, -6, 0.0);
	for (char& c : total_positive_score_label)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

	//Shot precision
	string precision_label = "Precision: ";
	float total_shots = 0;
	float shots_hit = 0;
	for (int i = 0; i < scoreBoards.size(); i++) {
		total_shots += scoreBoards[i].bullets_fired;
		shots_hit += scoreBoards[i].bullets_on_target;
	}
	float precision = (total_shots>0)? (shots_hit / total_shots) * 100 : 0;
	convert.str("");
	convert << precision;
	precision_label.append(convert.str());
	precision_label.append("%");
	glColor4ub(0, 0, 0, 255);
	glRasterPos3f(-19, -2, 0.0);
	for (char& c : precision_label)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

	//head shots
	string shots_on_head_label = "HeadShots: ";
	int shots_on_head = 0;
	for (int i = 0; i < scoreBoards.size(); i++) {
		shots_on_head += scoreBoards[i].headshots;
	}
	convert.str("");
	convert << shots_on_head;
	shots_on_head_label.append(convert.str());
	glColor4ub(0, 0, 0, 255);
	glRasterPos3f(-19, 0, 0.0);
	for (char& c : shots_on_head_label)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

	//body shots
	string shots_on_body_label = "Shots on target body: ";
	int shots_on_body = 0;
	for (int i = 0; i < scoreBoards.size(); i++) {
		shots_on_body += scoreBoards[i].bodyshots;
	}
	convert.str("");
	convert << shots_on_body;
	shots_on_body_label.append(convert.str());
	glColor4ub(0, 0, 0, 255);
	glRasterPos3f(-19, 2, 0.0);
	for (char& c : shots_on_body_label)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

	//shots on target
	string shots_on_target_label = "Shots fired on target: ";
	int shots_on_target = 0;
	for (int i = 0; i < scoreBoards.size(); i++) {
		shots_on_target += scoreBoards[i].bullets_on_target;
	}
	convert.str("");
	convert << shots_on_target;
	shots_on_target_label.append(convert.str());
	glColor4ub(0, 0, 0, 255);
	glRasterPos3f(-19, 4, 0.0);
	for (char& c : shots_on_target_label)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

	//shots fired
	string shots_fired_label = "Shots fired: ";
	int shots = 0;
	for (int i = 0; i < scoreBoards.size(); i++) {
		shots += scoreBoards[i].bullets_fired;
	}
	convert.str("");
	convert << shots;
	shots_fired_label.append(convert.str());
	glColor4ub(0, 0, 0, 255);
	glRasterPos3f(-19, 6, 0.0);
	for (char& c : shots_fired_label)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

	//maches played label
	string matches_played_label = "Matches played: ";
	convert.str("");
	convert << scoreBoards.size();
	matches_played_label.append(convert.str());
	glColor4ub(0, 0, 0, 255);
	glRasterPos3f(-19, 8, 0.0);
	for (char& c : matches_played_label)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

	string general_stats = "General Stats:";
	glColor4ub(0, 0, 0, 255);
	glRasterPos3f(-19, 12, 0.0);
	for (char& c : general_stats)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

	string scoreboard_label = "SCORE BOARD";
	glColor4ub(0, 0, 0, 255);
	glRasterPos3f(-2.5, 17, 0.0);
	for (char& c : scoreboard_label)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

	glBegin(GL_LINES);
	glColor4f(0.2,0.2,0.2,0.4);
	glVertex2f(0,15);
	glVertex2f(0, -20);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0.5, 0.5, 0.5, 0.8);
	glVertex2f(-20, 20);
	glVertex2f(20, 20);
	glVertex2f(20, -20);
	glVertex2f(-20, -20);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1,1,1,0.4);
	glVertex2f(-30, 30);
	glVertex2f(30,30);
	glVertex2f(30, -30);
	glVertex2f(-30, -30);
	glEnd();
}

void print_timer(int difficulty_selected) {

	//Cor da fonte
	switch (difficulty_selected)
	{
	case EASY:
		glColor3ub(0, 255, 0);
		break;
	case MEDIUM:
		glColor3ub(255, 255, 0);
		break;
	case HARD:
		glColor3ub(255, 0, 0);
		break;
	default:
		glColor3ub(255, 255, 255);
		break;
	}
	
	//glColor3f(1,0,0);
	//Posição da palavra
	glRasterPos3f(-29.0, 28.5, 0.0);

	//Uso do "for" para escrever mais de um caracter
	for (char& c : timer.timer)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-30, 30);
	glVertex2f(-25, 30);
	glVertex2f(-25, 28);
	glVertex2f(-30, 28);
	glEnd();

}

void print_bullet_counter() {

	string counter = "";

	ostringstream convert;

	convert.str("");
	convert << bullets_on_chamber;
	counter.append(convert.str());
	counter.append(" / --");

	if (warning_no_bullets) 
		glColor3ub(255, 0, 0);
	else
		glColor3ub(255, 255, 255);

	glRasterPos3f(24.0, -28.5, 0.0);
	for (char& c : counter)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(30, -30);
	glVertex2f(23, -30);
	glVertex2f(23, -26);
	glVertex2f(30, -26);
	glEnd();

	if (warning_no_bullets) {
		string warning = "[R] - RELOAD";
		glColor4ub(255, 255, 255, 100);
		glRasterPos3f(-1.5, -17.0, 0.0);
		for (char& c : warning)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

		string warning2 = "No bullets";
		glColor4ub(255, 0, 0, 200);
		glRasterPos3f(-1.0, -2.0, 0.0);
		for (char& c : warning2)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
	}

}

void reloading_time(int value) {
	if (value != 0) {
		is_reloading = true;
		glutTimerFunc(700, reloading_time, 0);
	}
	else {
		is_reloading = false;
		bullets_on_chamber = MAX_BULLETS_ON_CHAMBER;
	}

	glutPostRedisplay();
}

void no_bullets_warning_time(int value) {
	if (value != 0) {
		warning_no_bullets = true;
		glutTimerFunc(500, no_bullets_warning_time, 0);
	}
	else {
		warning_no_bullets = false;
	}

	glutPostRedisplay();
}

void score_hit_warning_time(int value) {
	if (value != 0) {
		score_hit = true;
		glutTimerFunc(500, score_hit_warning_time, 0);
	}
	else {
		score_hit = false;
	}

	glutPostRedisplay();
}

void Visualizacao() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(50, 1, 0.1, 10000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void draw_2D_hud() {

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-30, 30, -30, 30);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//drawing HUD elements

	//timer
	if (is_time_running)
		print_timer(MAP.difficulty_selected(cam.cam_x, cam.cam_z));
	else
		timer.reset_timer();

	//	crosshair
	if (!IS_TAB_PRESSED) {
		glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(-0.05, 0.8);
		glVertex2f(0.05, 0.8);
		glVertex2f(0.05, 0.3);
		glVertex2f(-0.05, 0.3);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(-0.05, -0.8);
		glVertex2f(0.05, -0.8);
		glVertex2f(0.05, -0.3);
		glVertex2f(-0.05, -0.3);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(-0.5, -0.05);
		glVertex2f(-0.5, 0.05);
		glVertex2f(-0.2, 0.05);
		glVertex2f(-0.2, -0.05);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.5, -0.05);
		glVertex2f(0.5, 0.05);
		glVertex2f(0.2, 0.05);
		glVertex2f(0.2, -0.05);
		glEnd();
	}

	//scoreboard (if TAB is pressed)
	if (IS_TAB_PRESSED)
		print_scoreboard();

	//interaction indicator (start game)
	if (is_player_on_difficulty_floor && !is_game_active) {

		string aviso;
		switch (MAP.difficulty_selected(cam.cam_x,cam.cam_z))
		{
		case EASY:
			aviso = "Press SPACEBAR to start (easy mode)";
			break;
		case MEDIUM:
			aviso = "Press SPACEBAR to start (medium mode)";
			break;
		case HARD:
			aviso = "Press SPACEBAR to start (hard mode)";
			break;
		default:
			aviso = "";
			break;
		}

		glColor3ub(0, 255, 255);
		//glColor3f(1,0,0);
		//Posição da palavra
		glRasterPos3f(-4.5, -5.0, 0.0);

		//Uso do "for" para escrever mais de um caracter
		for (char& c : aviso)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

	}

	//reloading animation
	if (is_reloading) {
		string aviso = "Reloading...";

		glColor4ub(255, 255, 255, 100);
		//glColor3f(1,0,0);
		//Posição da palavra
		glRasterPos3f(-2, -7.0, 0.0);

		//Uso do "for" para escrever mais de um caracter
		for (char& c : aviso)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}

	//score hit animation
	if (score_hit) {
		ostringstream convert;
		string score = "";

		convert.str("");
		convert << last_score;
		score.append(convert.str());
		score.append(" pts.");

		if(last_score < 0) //negative points
			glColor3ub(255,0,0);
		else
			glColor3ub(0, 255, 0);
		glRasterPos3f(1.0,1.0,0.0);
		for (char& c : score)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

		//target hit image (where the last shot hit on the target)	

		//head
		glBegin(GL_QUADS);
		if(last_score != HEAD_SHOT_SCORE)
			glColor3f(1.0, 1.0, 1.0);
		else
			glColor3f(1.0, 0.0, 0.0);
		glVertex3f(26.0, 9.8, 0.0);
		glVertex3f(27.0, 9.8, 0.0);
		glVertex3f(27.0, 8.5, 0.0);
		glVertex3f(26.0, 8.5, 0.0);
		glEnd();

		//body
		glBegin(GL_QUADS);
		if (last_score != BODY_SHOT_SCORE)
			glColor3f(1.0, 1.0, 1.0);
		else
			glColor3f(1.0, 0.0, 0.0);
		glVertex3f(25.3, 8.5, 0.0);
		glVertex3f(27.7, 8.5, 0.0);
		glVertex3f(27.7, 4.0, 0.0);
		glVertex3f(25.3, 4.0, 0.0);
		glEnd();

		string where_hit = "Bullet Hit:";
		glColor3ub(255, 255, 255);
		glRasterPos3f(24.5, 10.5, 0.0);
		for (char& c : where_hit)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);

		//background square
		glBegin(GL_QUADS);
		glColor3f(0.0,0.0,0.0);
		glVertex3f(24.0, 11.5, 0.0);
		glVertex3f(29.0, 11.5, 0.0);
		glVertex3f(29.0, 3.3, 0.0);
		glVertex3f(24.0, 3.3, 0.0);
		glEnd();

	}

	//bullet count
	print_bullet_counter();

	//interaction buttons label
	if (current_interaction_object.get_hud_label() != "") {
		glColor3ub(0, 255, 255);
		glRasterPos3f(-4.5, -3.0, 0.0);
		for (char& c : current_interaction_object.get_hud_label())
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

		string interaction_instruction = "[E] Interaction";
		glColor3ub(0, 255, 255);
		glRasterPos3f(-2.5, -5.0, 0.0);
		for (char& c : interaction_instruction)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);


	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}


void DesenhaCena(void)
{

	// Limpa a janela com a cor especificada como cor de fundo
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// Para habilitar a transparência
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_FLAT);

	Visualizacao();
	cam.control(mouse_pos_x, mouse_pos_y, is_only_refresh);
	cam.updateCamera();
	if (is_only_refresh)
		is_only_refresh = false;

	//draw map
	MAP.draw_map();

	draw_2D_hud();

	glutSwapBuffers();

	MAP.CalculateVectorNormal(MAP.targets_easy[0].shapes[0]);

	if (MAP.difficulty_selected(cam.cam_x, cam.cam_z) != NO_DIFFICULTY) {
		is_player_on_difficulty_floor = true;
	}

}


// Inicializa aspectos do rendering
void Inicio(void) {
	glClearColor(0.2f, 0.5f, 1.0f, 0.5f);  // cor de fundo da janela
	DUMMY_INTERACTION.hud_label = "";
}

void teclasNormais(unsigned char tecla, int x, int y) {

	if (toupper(tecla) == 'S') {
		IS_S_DOWN = true;
	}
	else {
		if (toupper(tecla) == 'W') {
			IS_W_DOWN = true;
		}
		else {
			if (toupper(tecla) == 'A') {
				IS_A_DOWN = true;
			}
			else {
				if (toupper(tecla) == 'D') {
					IS_D_DOWN = true;
				}
			}
		}
	}

	glutPostRedisplay();

}

void teclasNormaisup(unsigned char tecla, int x, int y) {

	if (toupper(tecla) == 'S') {
		IS_S_DOWN = false;
	}
	else {
		if (toupper(tecla) == 'W') {
			IS_W_DOWN = false;
		}
		else {
			if (toupper(tecla) == 'A') {
				IS_A_DOWN = false;
			}
			else {
				if (toupper(tecla) == 'D') {
					IS_D_DOWN = false;
				}
				else {
					if (toupper(tecla) == 'L') {
						cam.is_mouse_in = false;
					}
					else {
						if (tecla == ' ') {
							if (is_player_on_difficulty_floor && !is_game_active) {
								timer.reset_timer();
								is_time_running = true;
								is_game_active = true;
								scoreBoards.push_back(Score_Manager());
								round_selected++;
							}
						}
						else {
							if (toupper(tecla) == 'R') {
								glutTimerFunc(1, reloading_time, 1);
							}
							else {
								if (toupper(tecla) == 'E') {
									if (current_interaction_object.get_hud_label() != "") {
										current_interaction_object.execute_interaction();
									}
								}
								else {
									if (toupper(tecla) == '	') {
										IS_TAB_PRESSED = !IS_TAB_PRESSED;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	glutPostRedisplay();

}

void mouse_movement(int button, int state, int x, int y) {

	

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && cam.is_mouse_in == false) {

		glutWarpPointer(SCREEN_WIDTH / 2, SCREEN_HEIGTH / 2);
		mouse_pos_x = SCREEN_WIDTH / 2;
		mouse_pos_y = SCREEN_HEIGTH / 2;
		cam.is_mouse_in = true;
		cam.cam_yaw = 15.0;
		cam.cam_pitch = 6.0;
		previous_mouse_pos_x = x - (SCREEN_WIDTH / 2);
		previous_mouse_pos_y = y - (SCREEN_HEIGTH / 2);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//testing targets collision (according to the difficulty selected) and shoot contabilization
		int missed_shot = 0;
		if (bullets_on_chamber > 0 && !is_reloading) {
			bullets_on_chamber--;

			if (is_game_active) {
				switch (MAP.difficulty_selected(cam.cam_x, cam.cam_z))
				{

				case EASY:
					for (int i = 0; i < MAP.targets_easy.size(); i++) {
						for (int j = 0; j < MAP.targets_easy[i].shapes.size(); j++) {
							if (cam.is_camera_aiming_at(MAP.targets_easy[i].shapes[j], MAP.targets_easy[i], scoreBoards[scoreBoards.size() - 1], EASY)) {
								if (MAP.targets_easy[i].is_active && !MAP.targets_easy[i].is_dead) {
									MAP.targets_easy[i].shapes[j].color = { 1.0, 0.0, 0.0 };
									MAP.targets_easy[i].is_active = false;
									MAP.targets_easy[i].is_dead = true;
									MAP.targets_easy[i].pitch = TARGET_PITCH_INACTIVE;
									if (j == 0) { //headshot
										last_score = HEAD_SHOT_SCORE;
										glutTimerFunc(1, score_hit_warning_time, 1);
									}
									else { //bodyshot
										last_score = BODY_SHOT_SCORE;
										glutTimerFunc(1, score_hit_warning_time, 1);
									}
								}
								else { //missed shot
									missed_shot ++;
								}

							}
							else { //missed shot
								missed_shot ++;
							}
						}
					}

					if (missed_shot == MAP.targets_easy.size()*2) {
						scoreBoards[scoreBoards.size() - 1].score(MISSED_SHOT);
					}
					else {
						scoreBoards[scoreBoards.size() - 1].score(last_score);
					}
					break;

				case MEDIUM:
					for (int i = 0; i < MAP.targets_medium.size(); i++) {
						for (int j = 0; j < MAP.targets_medium[i].shapes.size(); j++) {
							if (cam.is_camera_aiming_at(MAP.targets_medium[i].shapes[j], MAP.targets_medium[i], scoreBoards[scoreBoards.size() - 1], MEDIUM)) {
								if (MAP.targets_medium[i].is_active && !MAP.targets_medium[i].is_dead) {
									MAP.targets_medium[i].shapes[j].color = { 1.0, 0.0, 0.0 };
									MAP.targets_medium[i].is_active = false;
									MAP.targets_medium[i].is_dead = true;
									MAP.targets_medium[i].pitch = TARGET_PITCH_INACTIVE;
									if (j == 0) { //headshot
										last_score = HEAD_SHOT_SCORE;
										glutTimerFunc(1, score_hit_warning_time, 1);
									}
									else { //bodyshot
										last_score = BODY_SHOT_SCORE;
										glutTimerFunc(1, score_hit_warning_time, 1);
									}
								}
								else { //missed shot
									missed_shot ++;
								}

							}
							else { //missed shot
								missed_shot ++;
							}
						}
					}

					if (missed_shot == MAP.targets_medium.size()*2) {
						scoreBoards[scoreBoards.size() - 1].score(MISSED_SHOT);
					}
					else {
						cout << "marcando score " << last_score << endl;
						scoreBoards[scoreBoards.size() - 1].score(last_score);
					}
					break;

				case HARD:
					cout << "hard shot" << endl;
					for (int i = 0; i < MAP.targets_hard.size(); i++) {
						cout << "testando alvo " << i << endl;
						for (int j = 0; j < MAP.targets_hard[i].shapes.size(); j++) {
							if (cam.is_camera_aiming_at(MAP.targets_hard[i].shapes[j], MAP.targets_hard[i], scoreBoards[scoreBoards.size() - 1], HARD)) {
								if (MAP.targets_hard[i].is_active && !MAP.targets_hard[i].is_dead) {
									MAP.targets_hard[i].shapes[j].color = { 1.0, 0.0, 0.0 };
									MAP.targets_hard[i].is_active = false;
									MAP.targets_hard[i].is_dead = true;
									MAP.targets_hard[i].pitch = TARGET_PITCH_INACTIVE;
									if (j == 0) { //headshot
										last_score = HEAD_SHOT_SCORE;
										glutTimerFunc(1, score_hit_warning_time, 1);
									}
									else { //bodyshot
										last_score = BODY_SHOT_SCORE;
										glutTimerFunc(1, score_hit_warning_time, 1);
									}
								}
								else { //missed shot
									missed_shot ++;
								}

							}
							else { //missed shot
								missed_shot ++;
							}
						}
					}

					if (missed_shot == MAP.targets_hard.size()*2) {
						cout << "missed shot" << endl;
						bool hostage_hit = true;
						//test hostage shot
						for (int i = 0; i < MAP.hostages_hard.size(); i++) {
							for (int j = 0; j < MAP.hostages_hard[i].shapes.size(); j++) {
								if (cam.is_camera_aiming_at(MAP.hostages_hard[i].shapes[j], MAP.hostages_hard[i], scoreBoards[scoreBoards.size() - 1], HARD)) {
									if (MAP.hostages_hard[i].is_active && !MAP.hostages_hard[i].is_dead) {
										MAP.hostages_hard[i].shapes[j].color = { 1.0, 0.0, 0.0 };
										MAP.hostages_hard[i].is_active = false;
										MAP.hostages_hard[i].is_dead = true;
										MAP.hostages_hard[i].pitch = TARGET_PITCH_INACTIVE;
										scoreBoards[scoreBoards.size() - 1].score(HOSTAGE_SHOT_SCORE);
										last_score = HOSTAGE_SHOT_SCORE;
										hostage_hit = true;
										glutTimerFunc(1, score_hit_warning_time, 1);
									}
								}
							}
						}
						if(!hostage_hit)
							scoreBoards[scoreBoards.size() - 1].score(MISSED_SHOT);
					}
					else {
						scoreBoards[scoreBoards.size() - 1].score(last_score);
					}
					break;

				}
			}

		}
		else {
			if(!is_reloading)
				glutTimerFunc(1, no_bullets_warning_time, 1);
		}

	}

	glutPostRedisplay();
}

void mouse_passive(int x, int y) {

	if ((x - (SCREEN_WIDTH / 2)) != previous_mouse_pos_x || (y - (SCREEN_HEIGTH / 2)) != previous_mouse_pos_y) {

		float future_pitch = MOUSE_SENSIBILITY * ((SCREEN_HEIGTH / 2) - (mouse_pos_y + (y - (SCREEN_HEIGTH / 2))));

		mouse_pos_x += x - (SCREEN_WIDTH / 2);
		if (future_pitch <= 90 && future_pitch >= -90) {
			mouse_pos_y += y - (SCREEN_HEIGTH / 2);
		}
	}
	
	for (int i = 0; i < MAP.control_buttons.size(); i++) {
		for (int j = 0; j < MAP.control_buttons[i].shapes.size(); j++) {
			if (cam.is_camera_aiming_at_shape_for_interaction(MAP.control_buttons[i].shapes[j], MAP.control_buttons[i])) {
				current_interaction_object = MAP.control_buttons[i];
				break;
			}
			else {
				current_interaction_object = DUMMY_INTERACTION;
			}
		}
		if (current_interaction_object.get_hud_label() != "")
			break;
	}

	previous_mouse_pos_x = x - (SCREEN_WIDTH / 2);
	previous_mouse_pos_y = y - (SCREEN_HEIGTH / 2);
	glutPostRedisplay();
}

void teclasespeciais(int tecla, int x, int y) {
	if (tecla == GLUT_KEY_RIGHT) {
		if (round_selected < scoreBoards.size())
			round_selected++;
	}else{
		if (tecla == GLUT_KEY_LEFT) {
			if (round_selected > 1)
				round_selected--;
		}
		else {
			if (tecla == GLUT_KEY_UP) {
				MOUSE_SENSIBILITY += 0.05;
				is_only_refresh = true;
			}
			else {
				if (tecla == GLUT_KEY_DOWN) {
					if (MOUSE_SENSIBILITY > 0.05) {
						MOUSE_SENSIBILITY -= 0.05;
						is_only_refresh = true;
					}						
				}
				else {
					if (tecla == GLUT_KEY_SHIFT_L) {
						MOVEMENT_TIC += 0.001;
					}
					else {
						if (tecla == GLUT_KEY_CTRL_L) {
							cam.cam_y -= 0.6;
						}
					}
				}
			}
		}
	}

	glutPostRedisplay();
}

void teclasespeciaisup(int tecla, int x, int y) {
	if (tecla == GLUT_KEY_SHIFT_L) {
		MOVEMENT_TIC -= 0.001;
	}
	else {
		if (tecla == GLUT_KEY_CTRL_L) {
			cam.cam_y += 0.6;
		}
	}
}

void time_counter(int value) {

	if (is_time_running) {
		timer.updateTimer();
	}

	glutPostRedisplay();

	if (timer.seconds[0] == (MAX_ROUND_SECONDS_TIME/10) && timer.seconds[1] == (MAX_ROUND_SECONDS_TIME%10)) { //time limit reached
		is_time_running = false;
		is_game_active = false;
		timer.reset_timer();
	}

	glutTimerFunc(10, time_counter, 1);
}

void target_toggle(int value) {
	MAP.reload_target_pitches();
	glutPostRedisplay();
	glutTimerFunc(1500, target_toggle, 1);
}


// Parte principal - ponto de início de execução
// Cria janela
// Inicializa aspectos relacionados a janela e a geracao da imagem
// Especifica a função de callback de desenho
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	// Indica que deve ser usado um unico buffer para armazenamento da imagem e representacao de cores RGB
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Cria uma janela com o titulo especificado
	glutCreateWindow("Trabalho Pirâmide");
	glutReshapeWindow(SCREEN_WIDTH, SCREEN_HEIGTH);

	//Chama a função de tratamento de teclas comuns
	glutKeyboardFunc(teclasNormais);
	glutKeyboardUpFunc(teclasNormaisup);

	glutSpecialFunc(teclasespeciais);
	glutSpecialUpFunc(teclasespeciaisup);

	//passive mouse movement function
	glutMouseFunc(mouse_movement);
	glutPassiveMotionFunc(mouse_passive);

	//timer (only if player is scoring
	glutTimerFunc(10, time_counter, 1);
	glutTimerFunc(1500, target_toggle, 1);

	// Especifica para a OpenGL que funcao deve ser chamada para geracao da imagem
	glutDisplayFunc(DesenhaCena);

	// Executa a inicializacao de parametros de exibicao
	Inicio();

	// Dispara a "maquina de estados" de OpenGL
	glutMainLoop();

	return 0;
}
