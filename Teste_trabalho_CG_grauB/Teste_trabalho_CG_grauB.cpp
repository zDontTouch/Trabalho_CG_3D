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

using namespace std;
using namespace Globals;

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

Timer timer;

Camera_System cam;

vector<Score_Manager> scoreBoards{};

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

	//bullet count
	print_bullet_counter();

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
	glClearColor(0.2f, 0.0f, 0.0f, 1.0f);  // cor de fundo da janela
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
							}
						}
						else {
							if (toupper(tecla) == 'R') {
								glutTimerFunc(1, reloading_time, 1);
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

		bool missed_shot = false;
		if (bullets_on_chamber > 0) {
			bullets_on_chamber--;

			if (is_game_active) {
				switch (MAP.difficulty_selected(cam.cam_x, cam.cam_z))
				{

				case EASY:
					for (int i = 0; i < MAP.targets_easy.size(); i++) {
						for (int j = 0; j < MAP.targets_easy[i].shapes.size(); j++) {
							if (cam.is_camera_aiming_at(MAP.targets_easy[i].shapes[j], MAP.targets_easy[i], scoreBoards[scoreBoards.size() - 1])) {
								if (MAP.targets_easy[i].is_active && !MAP.targets_easy[i].is_dead) {
									MAP.targets_easy[i].shapes[j].color = { 1.0, 0.0, 0.0 };
									MAP.targets_easy[i].is_active = false;
									MAP.targets_easy[i].is_dead = true;
									MAP.targets_easy[i].pitch = TARGET_PITCH_INACTIVE;
									if (j == 0) { //headshot
										scoreBoards[scoreBoards.size() - 1].score(HEAD_SHOT_SCORE);
									}
									else { //bodyshot
										scoreBoards[scoreBoards.size() - 1].score(BODY_SHOT_SCORE);
									}
								}
								else { //missed shot
									missed_shot = true;
								}

							}
							else { //missed shot
								missed_shot = true;
							}
						}
					}

					if (missed_shot)
						scoreBoards[scoreBoards.size() - 1].score(MISSED_SHOT);
					break;

				}
			}

		}
		else {
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

	previous_mouse_pos_x = x - (SCREEN_WIDTH / 2);
	previous_mouse_pos_y = y - (SCREEN_HEIGTH / 2);
	glutPostRedisplay();
}

void teclasespeciais(int tecla, int x, int y) {
	if (tecla == GLUT_KEY_RIGHT) {
	}else{
		if (tecla == GLUT_KEY_LEFT) {
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

	if (timer.seconds[0] == MAX_ROUND_SECONDS_TIME[0] && timer.seconds[1] == MAX_ROUND_SECONDS_TIME[1]) { //time limit reached
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
