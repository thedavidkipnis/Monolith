#include "Projectile.h"

Projectile::Projectile(int w, int h, float posX, float posY) {
	width = w;
	height = h;
	x = posX;
	y = posY;

	speed = 2.0;
	direction = 0;
}

float Projectile::getY() {
	return y;
}
void Projectile::setY(float newY) {
	y = newY;
}
float Projectile::getX() {
	return x;
}
void Projectile::setX(float newX) {
	x = newX;
}

float Projectile::getHeight() {
	return height;
}
void Projectile::setHeight(float h) {
	height = h;
}
float Projectile::getWidth() {
	return width;
}
void Projectile::setWidth(float w) {
	width = w;
}

float Projectile::getSpeed() {
	return speed;
}
void Projectile::setSpeed(float sp) {
	speed = sp;
}

int Projectile::getDirection() {
	return direction;
}
void Projectile::setDirection(int dir) {
	direction = dir;
}
