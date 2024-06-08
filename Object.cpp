/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

OBJECT Class

Class for representing objects such as coins, chests, potions, etc. in the game world

*/

#include "Object.h"

Object::Object(int id, float x, float y, float w, float h) {
	objectID = id;
	xPos = x;
	yPos = y;

	width = w;
	height = h;

	centerX = xPos + (width / 2);
	centerY = yPos + (height / 2);

	hitbox = {};
	hitbox.x = x;
	hitbox.y = y;
	hitbox.h = h;
	hitbox.w = w;

	velX = 0;
	velY = 0;
}

void Object::adjustState(SDL_Rect* playerHitbox) {
	

	int collided = MathFunc::checkCollision(*playerHitbox, hitbox);
	switch (collided) {
		case -1:
			return;
			break;
		case 0:
			xPos = playerHitbox->x + playerHitbox->w + 1;
			break;
		case 1:
			yPos = playerHitbox->y + playerHitbox->h + 1;
			break;
		case 2:
			xPos = playerHitbox->x - hitbox.w - 1;
			break;
		case 3:
			yPos = playerHitbox->y - hitbox.h - 1;
			break;
	}

	hitbox.x = xPos;
	hitbox.y = yPos;

}

void Object::move() {

}

float Object::getXPos() {
	return xPos;
}
float Object::getYPos() {
	return yPos;
}
void Object::setXPos(float p_x) {
	xPos = p_x;
}
void Object::setYPos(float p_y) {
	yPos = p_y;
}
float Object::getCenterX() {
	return xPos + (width / 2);
}
float Object::getCenterY() {
	return yPos + (height / 2);
}
SDL_Rect* Object::getHitbox() {
	return &hitbox;
}
