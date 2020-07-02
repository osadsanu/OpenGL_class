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
private:

	vector2 m_pos;
	float m_angle;
	Rect *m_base;
	vector2 *lineBegin;
	vector2 *lineEnd;
	float m_aimAngle;
	Rect *m_cannon;

};
