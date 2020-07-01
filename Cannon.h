#pragma once
#include "Rect.h"

class Cannon
{
public:
	Cannon(vector2 *pos, vector2 *size);
	void draw();
private:

	vector2 m_pos;
	float m_angle;
	Rect *m_base;
	vector2 *lineBegin;
	vector2 *lineEnd;

	Rect *m_cannon;

};
