/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

OBJECT Class Header

Class for representing objects such as coins, chests, potions, etc. in the game world

*/

#pragma once

#include <SDL.h>
#include <MathFunc.h>

#include <stdio.h>

class Object
{
public:

	Object(int id, float x, float y, float w, float h);
	float getXPos();
	float getYPos();
	void setXPos(float p_x);
	void setYPos(float p_y);
	float getCenterX();
	float getCenterY();
	SDL_Rect* getHitbox();

	// adjusts location based on interaction with the player
	void adjustState(SDL_Rect* playerHitbox);
	void move();

private:

	int objectID;

	float xPos, yPos, width, height, centerX, centerY;

	float velX, velY;

	SDL_Rect hitbox;
};

