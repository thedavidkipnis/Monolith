#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <Sprite.h>
#include <Tile.h>
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
	float distanceToPoint(float x, float y);

	int checkCollision(SDL_Rect a, SDL_Rect b);

	SDL_Rect* getHitbox();

	void chasePlayer(float playerX, float playerY, std::vector<Tile> * barriers);

private:

	float width, height;
	float mPosX, mPosY;

	float MAX_VEL;
	float mVelX, mVelY;

	float acceleration_factor;
	float decceleration_factor;

	float last_known_up, last_known_down, last_known_left, last_known_right;

	SDL_Rect hitbox;
};

