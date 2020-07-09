#pragma once
#include "Rect.h"
#include <list>
#include "Ball.h"
class Cannon
{
public:
	Cannon(vector2 *pos, vector2 *size);
	void draw();
	void aimRotate(float);
	void shoot(std::list<Ball*> & );
	void update(float);
private:

	vector2 m_pos;
	float m_angle;
	float m_currentAngle;
	Rect *m_base;
	vector2 *lineBegin;
	vector2 *lineEnd;
	vector2* lineBegin_init;
	vector2* lineEnd_init;
	float m_aimAngle;
	Rect *m_cannon;

};

