/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

CIRCLE Class

Class for representing circular hitboxes

*/

#include "Circle.h"

Circle::Circle(float x, float y, float r) {
	centerX = x;
	centerY = y;
	radius = r;
}

float Circle::getCenterX() {
	return centerX;
}
float Circle::getCenterY() {
	return centerY;
}
void Circle::setCenterX(float x) {
	centerX = x;
}
void Circle::setCenterY(float y) {
	centerY = y;
}
float Circle::getRadius() {
	return radius;
}
