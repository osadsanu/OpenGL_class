#pragma once
#include "Vector.h"
#include "Rect.h"

class Tank {
public:
	Tank(vector2* pos, vector2* size);
	void draw();
	void update(float dt);
	void move(float x, float y);
private:
	vector2 *m_pos;
	vector2* m_CurrentPos;
	Rect* m_base;

};