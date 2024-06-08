/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

CIRCLE Class Header

Class for representing circular hitboxes

*/

#pragma once

class Circle
{
public:

	Circle(float x, float y, float r);

	float getCenterX();
	float getCenterY();
	void setCenterX(float x);
	void setCenterY(float y);
	float getRadius();

private:
	float centerX, centerY;
	float radius;
};

