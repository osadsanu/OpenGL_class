#include "Cannon.h"
#include <GL\freeglut.h>

Cannon::Cannon(vector2 *pos, vector2 *size) {
	m_base = new Rect(pos->x, pos->y, size->x, size->y);
	lineBegin = new vector2(pos->x, pos->y);
	lineEnd = new vector2 (pos->x, pos->y + 3);
}

void Cannon::draw() {
	m_base->draw();
	glPushMatrix();
	glColor3f(1, 0, 0.56f);
	glBegin(GL_LINES);
		glVertex3f(lineBegin->x, lineBegin->y,0);
		glVertex3f(lineEnd->x, lineEnd->y,0);
	glEnd();
	glPopMatrix();

}
