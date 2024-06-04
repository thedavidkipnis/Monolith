#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <Sprite.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <Entity.h>

class Player
{
	public:

		//Maximum axis velocity of the dot
		int MAX_VEL;

		//Initializes the variables
		Player(int w, int h, float posX, float posY);

		//Takes key presses and adjusts the dot's velocity
		void handleEvent(SDL_Event& e);

		int checkCollision(SDL_Rect a, SDL_Rect b);

		//Moves the dot
		void move(float screenWidth, float screenHeight, std::vector<SDL_Rect> & barriers);

		void attack(SDL_Event& e);

		float getXPos();
		float getYPos();
		float getCenterX();
		float getCenterY();
		void setXPos(float p_x);
		void setYPos(float p_y);
		float getHeight();
		float getWidth();
		SDL_Rect* getHitbox();

		int getAttackDir();

		int returnDirection();

	private:
		int width, height;

		float mPosX, mPosY;

		float mVelX, mVelY;

		float acceleration_factor;
		float decceleration_factor;

		bool up, down, left, right;
		float last_known_up, last_known_down, last_known_left, last_known_right;

		int attackDir;

		SDL_Rect hitbox;
};

