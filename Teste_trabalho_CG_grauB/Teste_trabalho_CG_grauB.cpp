#include "stdafx.h"
#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include <stdio.h>
#include "Globals.h"
#include "Timer.h"
#include "Map.h"

#include "Camera_System.h"

using namespace std;
using namespace Globals;

float angle = 0;

bool is_only_refresh = false;
bool is_time_running = false;

int previous_mouse_pos_x = 0;
int previous_mouse_pos_y = 0;
int mouse_pos_x = 0;
int mouse_pos_y = 0;

Timer timer;

Camera_System cam;

void print_timer() {

	int i = 0;

	//Cor da fonte
	glColor3ub(255, 255, 255);
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
	if(is_time_running)
		print_timer();

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
						if (toupper(tecla) == 'T') {
							is_time_running = true;
							cout << "start" << endl;
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
		/*if ((x - (SCREEN_WIDTH / 2)) != previous_mouse_pos_x || (y - (SCREEN_HEIGTH / 2)) != previous_mouse_pos_y) {

			float future_pitch = MOUSE_SENSIBILITY * ((SCREEN_HEIGTH / 2) - (mouse_pos_y + (y - (SCREEN_HEIGTH / 2))));

			mouse_pos_x += x - (SCREEN_WIDTH / 2);
			if (future_pitch <= 90 && future_pitch >= -90) {
				mouse_pos_y += y - (SCREEN_HEIGTH / 2);
			}
		}

		previous_mouse_pos_x = x - (SCREEN_WIDTH / 2);
		previous_mouse_pos_y = y - (SCREEN_HEIGTH / 2);*/
		cout << "click" << endl;
		return;
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
	glutTimerFunc(10, time_counter, 1);
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

	// Especifica para a OpenGL que funcao deve ser chamada para geracao da imagem
	glutDisplayFunc(DesenhaCena);

	// Executa a inicializacao de parametros de exibicao
	Inicio();

	// Dispara a "maquina de estados" de OpenGL
	glutMainLoop();

	return 0;
}
