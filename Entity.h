/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

ENTITY Class Header

Non-player entities in the game, both hostile and non-hostile

*/

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <Sprite.h>
#include <Tile.h>
#include <MathFunc.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <cmath>

class Entity
{
public:

	Entity(int w, int h, float posX, float posY);

	float getXPos();
	float getYPos();
	float getCenterX();
	float getCenterY();
	void setXPos(float p_x);
	void setYPos(float p_y);

	// returns the distance from Entity's center to the point
	float distanceToPoint(float x, float y);

	// returns a ptr to the entity's hitbox
	SDL_Rect* getHitbox();

	// basic AI for moving after the player
	void chasePlayer(float playerX, float playerY, std::vector<Tile> * barriers);

private:

	float width, height;
	float mPosX, mPosY;

	float MAX_VEL;
	float mVelX, mVelY;

	float acceleration_factor;
	float decceleration_factor;

	SDL_Rect hitbox;
};

