#include "Tank.h"
#include <GL\freeglut.h>
#include <iostream>


Tank::Tank(vector2* pos, vector2* size) {
	m_base = new Rect(pos->x, pos->y, size->x, size->y);
	m_pos = new vector2(pos->x,pos->y);
	m_CurrentPos = new vector2(pos->x, pos->y);;
}

void Tank::update(float dt) {
	float adjust = dt *5;

	if (m_CurrentPos->x < m_pos->x) {
		m_CurrentPos->x += adjust;
	}
	//std::cout << "Current x:" << m_CurrentPos->x << "targetX: " << m_pos->x << std::endl;

	if (m_CurrentPos->y < m_pos->y) {
		m_CurrentPos->y += adjust;
	}

	if (m_CurrentPos->x > m_pos->x) {
		m_CurrentPos->x -= adjust;
	}
	if (m_CurrentPos->y > m_pos->y) {
		m_CurrentPos->y -= adjust;
	}
	
	m_base->m_pos->x = m_CurrentPos->x;
	m_base->m_pos->y = m_CurrentPos->y;
}

void Tank::draw() {

	m_base->m_pos->x = m_CurrentPos->x;
	m_base->m_pos->y = m_CurrentPos->y;
	m_base->draw();
}

void Tank::move(float x, float y) {
	m_pos->x += x;
	m_pos->y += y;
}

