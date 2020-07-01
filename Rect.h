#pragma once
#include "Ball.h"
#include "Vector.h"
#define steps 30





class Rect
{
public:
	Rect(float, float, float, float);
	void draw();
	bool isCollision(Ball*);
	void resetColor();

	vector2* m_P1, * m_P2, * m_P3, * m_P4;
private:
	vector2* m_pos;


	float m_colorR, m_colorG, m_colorB;
};