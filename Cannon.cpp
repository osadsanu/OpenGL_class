#include "Cannon.h"
#include <GL\freeglut.h>
#include <iostream>

Cannon::Cannon(vector2 *pos, vector2 *size) {
	m_base = new Rect(pos->x, pos->y, size->x, size->y);
	lineBegin = new vector2(pos->x, pos->y);
	lineEnd = new vector2 (pos->x, pos->y + 3);
	
	lineBegin_init = new vector2(pos->x, pos->y);
	lineEnd_init = new vector2(pos->x, pos->y + 3);

	m_aimAngle = 0;
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


void Cannon::aimRotate(float deltaAngle) {
	m_angle += deltaAngle;
	
	std::cout << "angle:" << deltaAngle <<"x: " << lineEnd->x << " y: " <<lineEnd->y << std::endl;
}
void Cannon::update(float dt) {
	float adjust = dt*0.5f;
	if(equalFloat( m_currentAngle, m_angle )){
		return;
	}
	std::cout << "Current Angle:" << m_currentAngle << "targetAngle: " << m_angle << std::endl;
	if (m_currentAngle < m_angle) {
		m_currentAngle += adjust;
		vector2 end = rotateAroundPt(m_currentAngle, lineEnd_init, lineBegin_init);
		lineEnd->x = end.x;
		lineEnd->y = end.y;
	}
	if (m_currentAngle > m_angle) {
		m_currentAngle -= adjust;
		vector2 end = rotateAroundPt(m_currentAngle, lineEnd_init, lineBegin_init);
		lineEnd->x = end.x;
		lineEnd->y = end.y;
	}
}
void Cannon::shoot(std::list<Ball*>& ball) {
	Ball* aux = new Ball(0.5f);
	aux->setInitVel(lineEnd->x, lineEnd->y , 0);
	aux->setPosition(lineEnd->x, lineEnd->y,0);
	/*
	aux->setPosition(-5 + (rand() / (float)RAND_MAX) * 10, -5 + (rand() / (float)RAND_MAX) * 10, 0.0f);
	aux->setInitVel(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 0.0f);
	*/

	ball.push_back(aux);
}

