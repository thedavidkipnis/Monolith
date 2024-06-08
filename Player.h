/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

PLAYER Class Header

Keeps track of the playable character mechanics, inventory, and stats

*/

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <Sprite.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <Entity.h>
#include <Tile.h>
#include <MathFunc.h>

class Player
{
	public:

		// player's maximum velocity
		int MAX_VEL;

		Player(int w, int h, float posX, float posY);

		// handles user input to see if it affects the player
		void handleEvent(SDL_Event& e);

		// moves the player
		void move(float screenWidth, float screenHeight, std::vector<Tile> * barriers);

		// moves player into room once they reach an open doorway
		void moveIntoRoom();

		// handles user input to see if player is attacking
		void attack(SDL_Event& e);

		float getXPos();
		float getYPos();
		float getXVel();
		float getYVel();
		float getCenterX();
		float getCenterY();
		void setXPos(float p_x);
		void setYPos(float p_y);
		float getHeight();
		float getWidth();
		SDL_Rect* getHitbox();

		// returns which direction user
		int getAttackDir();

		// returns which direction user is moving
		int returnMovementDirection();

	private:
		int width, height;

		float mPosX, mPosY;

		float mVelX, mVelY;

		float acceleration_factor;
		float decceleration_factor;

		bool up, down, left, right;

		int attackDir;

		SDL_Rect hitbox;
};

