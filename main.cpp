#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <list>
#include "Ball.h"
#include "Rect.h"
#include "Cannon.h"

using namespace std;

float width, height;

int frame = 0, currentTime, timebase = 0, oldTime;

float dt;
float pos;
float vel;
char* s;
const int maxBall = 1; // 100 350fps; //250 100fps
//Ball* ball[maxBall];
list < Ball* > ball;
Rect* rect1;
Cannon* cannon;


const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 3.0f, 0.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void axis(void)
{
	/**Lienas para dibujar el Plano*/


	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3d(0, -15, 0);
	glVertex3d(0, 15, 0);
	glEnd();

	for (float i = -15; i < 15; i++) {
		glBegin(GL_LINES);
		glVertex3f(0.1f, i, 0);
		glVertex3f(-0.1f, i, 0);
		glEnd();
	}


}
void grid() {
	glPushMatrix();
	glColor3f(0.7f, 0.7f, 0.7f);
	for (int x = -14; x < 14; x++) {
		glBegin(GL_LINES);
		glVertex3f(14.0f, 0, x);
		glVertex3f(-14.0f, 0, x);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(x, 0, 14.0f);
		glVertex3f(x, 0, -14.0f);
		glEnd();

	}
	glPopMatrix();
}

void initLights() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

}

void changeViewPort(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(52.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void UpdateFPS() {
	frame++;
	if (currentTime - timebase > 1000) {
		int n = sprintf_s(s, 16, "FPS:%4.2f",
			frame * 1000.0 / ((double)currentTime - (double)timebase));
		timebase = currentTime;
		frame = 0;
		glutSetWindowTitle(s);
	}
}

bool init()
{
	srand(time(NULL));
	s = new char[16];
	rect1 = new Rect(0, 0, 3, 2);
	cannon = new Cannon(new vector2(0, 0),new  vector2(1.5f, 1.5f));

	for (int i = 0; i < maxBall; i++) {
		Ball* aux = new Ball(0.5f);
		aux->setPosition(-5 + (rand() / (float)RAND_MAX) * 10, -5 + (rand() / (float)RAND_MAX) * 10, 0.0f);
		aux->setInitVel(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 0.0f);
		aux->setGravity(-i);
		ball.push_back(aux);
	}






	glClearColor(0.93f, 0.93f, 0.93f, 0.0f);
	//initLights();
	width = 800.0f;
	height = 800.0f;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(52.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	return true;
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
		dt = 0;
	if (key == 'd') {
		cannon->aimRotate(2 *3.1415926535/180);
	}
	if (key == 'a') {
		cannon->aimRotate(-2 * 3.1415926535 / 180);
	}
	if (key == ' ') {
		cannon->shoot(ball);
	}
}

void updateData(float dt) {

	rect1->resetColor();
	
	//for (int i = 0; i < maxBall; i++) {
	//	ball[i]->resetColor();
	//	ball[i]->update(dt);
	//	rect1->isCollision(ball[i]);
	//	//FrameNumer Frame ID
	//	for (int d = 0; d < maxBall; d++) {
	//		if (i == d)continue;
	//		ball[i]->isCollision(ball[d]);
	//	}
	//}

	list <Ball*>::iterator it;
	for (it = ball.begin(); it != ball.end(); ++it) {
		(*it)->resetColor();
		(*it)->update(dt);
		rect1->isCollision((*it));
		list <Ball*>::iterator s_it;
		for (s_it = ball.begin(); s_it != ball.end(); ++s_it) {
			if (s_it == it)continue;
			(*it)->isCollision(*s_it);
		}
	}

	cannon->update(dt);

}


void draw() {
	//cout <<  << "time:" << time << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glLoadIdentity();

	gluLookAt(0, 0, 15, 0, 0, 0, 0, 1, 0);

	/*for (int i = 0; i < maxBall; i++) {
		ball[i]->draw();
	}*/

	list <Ball*>::iterator it;
	for (it = ball.begin(); it != ball.end(); ++it) {
		(*it)->draw();
	}

	//rect1->draw();
	
	cannon->draw();

	glutSwapBuffers();

}


void render()
{
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	dt = (currentTime - oldTime) / 1000.0f;
	updateData(dt);
	draw();
	UpdateFPS();
	oldTime = currentTime;
	glutPostRedisplay();
}
bool leftMouseButtonDown;
bool leftMouseButtonUp;
int mouseXPos;
int mouseYPos;

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		leftMouseButtonDown = (state == GLUT_DOWN);
		leftMouseButtonUp = (state == GLUT_UP);

		if (leftMouseButtonDown) {
			cout << "left Down: " << "mousePosX: " << x << " mousePosY: " << y << endl;
			if (x < 260) {
				cout << "left Side" << endl;
			}
			else if (x > 260 && x < 535) {
				cout << "central Side" << endl;
				/*for (int i = 0; i < maxBall; i++) {
					ball[i]->restart();
					ball[i]->setPosition(-5 + (rand() / (float)RAND_MAX) * 10, -5 + (rand() / (float)RAND_MAX) * 10, 0.0f);
					ball[i]->setInitVel(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 0.0f);
				}*/
				list <Ball*>::iterator it;
				for (it = ball.begin(); it != ball.end(); ++it) {
					(*it)->restart();
					(*it)->setPosition(-5 + (rand() / (float)RAND_MAX) * 10, -5 + (rand() / (float)RAND_MAX) * 10, 0.0f);
					(*it)->setInitVel(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 0.0f);
				}
			}
			else
			{
				cout << "right Side" << endl;
			}

		}
		if (leftMouseButtonUp) {
			cout << "left Up: " << "mousePosX: " << x << " mousePosY: " << y << endl;
		}
	}
}

int main(int argc, char* argv[]) {
	pos = 11;
	vel = 0;
	dt = 0;
	// Initialize GLUT
	glutInit(&argc, argv);
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// Set the window size
	glutInitWindowSize(800, 800);
	// Create the window with the title "Hello,GL"
	glutCreateWindow("Hello, GL");
	// Bind the two functions (above) to respond when necessary
	glutReshapeFunc(changeViewPort);

	glutDisplayFunc(&render);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	if (!init())
		return 1;

	glutMainLoop();
	return 0;
}