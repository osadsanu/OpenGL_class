#pragma once
#include <cmath>
class vector2
{
public:
	vector2() {}
	;
	vector2(float X, float Y) {
		x = X;
		y = Y;
	}
	float x, y;

	
private:
};

inline vector2 rotateAroundPt(float angle, vector2* point, vector2* root)
{
	float theta = angle;

	float xf, yf;

	// update theta anticlockwise rotation 

	// check overflow 
	if (theta >= (2.0 * 3.14159))
		theta = theta - (2.0 * 3.14159);

	// actual calculations.. 
	xf = root->x + ((float)(point->x - root->x) * cos(theta))
		- ((float)(point->y - root->y) * sin(theta));
	yf = root->y + ((float)(point->x - root->x) * sin(theta))
		+ ((float)(point->y - root->y) * cos(theta));

	// drawing the centre point 

	// drawing the rotating point 
	//drawPoint(root->x, root->y, xf, yf);

	// creating a delay 
	// so that the point can be noticed 
	return (vector2(xf, yf));

}