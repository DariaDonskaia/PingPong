/////////////////////*
//Game: Ping-Pong
//Auth:Daria Donskaya
//
/////////////////////*
#include "glut.h"
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <sstream>
#pragma warning(disable: 4996)

void initGL(int height, int width) {
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
GLfloat posXR = 10.0f;
GLfloat posYR = 250.0f;
GLfloat posZ = 0.0f;
GLfloat posXB = 200.0f;
GLfloat posYB = 200.0f;
void renderBall() 
{
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(posXB, posYB);
	glVertex2f(posXB + 10.0f, posYB);
	glVertex2f(posXB + 10.0f, posYB - 10.0f);
	glVertex2f(posXB, posYB - 10.0f);
	glEnd();
}
void renderRect() 
{
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(posXR, posYR);
	glVertex2f(posXR + 10.0f, posYR);
	glVertex2f(posXR + 10.0f, posYR - 80.0f);
	glVertex2f(posXR, posYR - 80.0f);
	glEnd();
}
GLfloat posXR2 = 370.0f;
GLfloat posYR2 = 250.0f;
GLfloat posZ22 = 0.0f;


void renderRect2() 
{
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(posXR2, posYR2);
	glVertex2f(posXR2 + 10.0f, posYR2);
	glVertex2f(posXR2 + 10.0f, posYR2 - 80.0f);
	glVertex2f(posXR2, posYR2 - 80.0f);
	glEnd();
}
std::string int2str(int x) {
	std::stringstream ss;
	ss << x;
	return ss.str();
}

void menu()
{
	  

}
void drawText(float x, float y, char *text ) 
{	
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen(text);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}

int score_left = 0;
int score_right = 0;
void Score() {
	std::string s = "Count " + std::to_string(score_left) + ':' + std::to_string(score_right);
    char* cstr = &s[0u];
	drawText(400 / 2 - 10, 400 - 34, cstr);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Score();
	renderRect();
	renderBall();
	renderRect2();
	glutSwapBuffers();
}
float speed = 0.09f;
void moveB(float angle)
{
	float y = sin(angle * 3.14159265/ 180);
	float x = cos(angle * 3.14159265 / 180);
		posXB = posXB + x*speed;
		posYB = posYB + y*speed;
	//std::cout << sin(3.14159265) << ":" << cos(3.14159265) << std::endl;
}
int dir = -1;
float angle_ = 180.0f;
void MoveBall() 
{
	if (posXB < 0) {
		score_right++;
		 posXB = 200.0f;
		 posYB = 200.0f;
	}
	if (posXB > 400) {
		score_left++;
		posXB = 200.0f;
		posYB = 200.0f;
	
	}
	if ((posXB < posXR + 10.0f && posYB<posYR && posYB>posYR - 80.0f && posXB>posXR) || (posXB > posXR2 - 10.0f && posYB<posYR2 && posYB>posYR2 - 80.0f && posXB < posXR2))
		angle_ -= rand() % (200 - 120 + 1) + 200;
	if ((posYB < 0 || posYB > 400)) {
		angle_ =  angle_*dir;
		std::cout << angle_;
	}	
	moveB(angle_);
}

void control(unsigned char key, int x, int y)
{

	if (GetAsyncKeyState(0x57))
		glTranslatef(posXR, posYR += 3.7, posZ);

	if (GetAsyncKeyState(0x53))
		glTranslatef(posXR , posYR -= 3.7, posZ);

	if (GetAsyncKeyState(0x49))
		glTranslatef(posXR2, posYR2 += 3.7, posZ);

	if (GetAsyncKeyState(0x4B))
		glTranslatef(posXR2, posYR2 -= 3.7, posZ);

	glutPostRedisplay();


}

void update()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	renderScene();
	MoveBall();
	glutPostRedisplay();
	glFlush();
}



void GameLoop() 
{
	
	update();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("myGame:PingPong");
	
	
	
	
	glutDisplayFunc(GameLoop);
	glutKeyboardFunc(control);
	initGL(400, 400);
	glColor3f(1.0f, 1.0f, 1.0f);
	// регистрация обратных вызовов

	glutMainLoop();
	
	// Основной цикл GLUT
	

	return 0;
}