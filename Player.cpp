/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

PLAYER Class

Keeps track of the playable character mechanics, inventory, and stats

*/

#include "Player.h"

Player::Player(int w, int h, float posX, float posY) {
	width = w;
	height = h;

	mPosX = posX;
	mPosY = posY;

	MAX_VEL = 5;
	mVelX = 0;
	mVelY = 0;

	up = false;
	down = false;
	left = false;
	right = false;

	acceleration_factor = 8.0;
	decceleration_factor = 16.0;

	hitbox = {};
	hitbox.h = height;
	hitbox.w = width;
	hitbox.x = mPosX;
	hitbox.y = mPosY;

	attackDir = -1;

}

void Player::handleEvent(SDL_Event& e) {
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w: up = true; break;
		case SDLK_s: down = true;break;
		case SDLK_a: left = true; break;
		case SDLK_d: right = true; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_w: up = false; break;
		case SDLK_s: down = false; break;
		case SDLK_a: left = false; break;
		case SDLK_d: right = false; break;
		}
	}
}

void Player::move(float screenWidth, float screenHeight, std::vector<Tile>* barriers) {

	for (int i = 0; i < barriers->size(); i++) {
		SDL_Rect curTile = barriers->at(i).getTile();
		int collisionCheck = MathFunc::checkCollision(hitbox, curTile);
		if (collisionCheck >= 0) {
			switch (collisionCheck) {
			case 0:
				mPosX = curTile.x - width;
				mVelX = 0;
				break;
			case 1:
				mPosY = curTile.y - height;
				mVelY = 0;
				break;
			case 2:
				mPosX = curTile.x + curTile.w + 1;
				mVelX = 0;
				break;
			case 3:
				mPosY = curTile.y + curTile.h + 1;
				mVelY = 0;
				break;
			}
		}
	}
	

	// accelerate left
	if (left && (mVelX / 100) > -1 * MAX_VEL && !right) {
		mVelX -= acceleration_factor;
	}
	// deccelerating left
	else if (mVelX < 0 && (!left || (right && left))) {
		if (abs(mVelX) < decceleration_factor) {
			mVelX = 0;
		}
		else {
			mVelX += decceleration_factor;
		}
	}

	// accelerate right
	if (right && (mVelX / 100) < MAX_VEL && !left) {
		mVelX += acceleration_factor;
	}
	// deccelerating right
	else if (mVelX > 0 && (!right || (right && left))) {
		if (abs(mVelX) < decceleration_factor) {
			mVelX = 0;
		}
		else {
			mVelX -= decceleration_factor;
		}
	}

	//Move the dot left or right
	mPosX += mVelX / 100;

	//If the dot went too far to the left or right
	if (mPosX < 0) {
		mVelX = 0;
		mPosX = 0;
	}
	if (mPosX > screenWidth - width) {
		mVelX = 0;
		mPosX = screenWidth - width;
	}

	// accelerate up
	if (up && (mVelY / 100) > -1 * MAX_VEL && !down) {
		mVelY -= acceleration_factor;
	}
	else if (mVelY < 0 && (!up || (up && down))) {
		if (abs(mVelY) < decceleration_factor) {
			mVelY = 0;
		}
		else {
			mVelY += decceleration_factor;
		}
	}

	// accelerate down
	if (down && (mVelY / 100) < MAX_VEL && !up) {
		mVelY += acceleration_factor;
	}
	else if (mVelY > 0 && (!down || (up && down))) {
		if (abs(mVelY) < decceleration_factor) {
			mVelY = 0;
		}
		else {
			mVelY -= decceleration_factor;
		}
	}


	//Move the dot up or down
	mPosY += mVelY / 100;

	//If the dot went too far up or down
	if (mPosY < 0) {
		mVelY = 0;
		mPosY = 0;
	}
	if (mPosY > screenHeight - height) {
		mVelY = 0;
		mPosY = screenHeight - height;
	}

	// move hitbox
	hitbox.x = mPosX;
	hitbox.y = mPosY;
}

void Player::moveIntoRoom() {

	mVelX = 0;
	mVelY = 0;

	if(mPosX >= 1119 && mPosY >= 440 && mPosY <= 520) {
		mPosX = 81;
		mPosY = 440;
	}
	else if (mPosX >= 580 && mPosX <= 700 && mPosY <= 80) {
		mPosX = 600;
		mPosY = 798;
	}
	else if (mPosX <= 81 && mPosY >= 440 && mPosY <= 520) {
		mPosX = 1118;
		mPosY = 440;
	}
	else if (mPosX >= 580 && mPosX <= 700 && mPosY >= 799) {
		mPosX = 600;
		mPosY = 81;
	}

	hitbox.x = mPosX;
	hitbox.y = mPosY;
}

void Player::attack(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: attackDir = 1; break;
		case SDLK_DOWN: attackDir = 3; break;
		case SDLK_LEFT: attackDir = 0; break;
		case SDLK_RIGHT: attackDir = 2; break;
		}
	}

	else if (e.type == SDL_KEYUP)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: attackDir = -1; break;
		case SDLK_DOWN: attackDir = -1; break;
		case SDLK_LEFT: attackDir = -1; break;
		case SDLK_RIGHT: attackDir = -1; break;
		}
	}
}

float Player::getXPos() {
	return mPosX;
}
float Player::getYPos() {
	return mPosY;
}

float Player::getXVel() {
	return mVelX;
}
float Player::getYVel() {
	return mVelY;
}

void Player::setXPos(float p_x) {
	mPosX = p_x;
}
void Player::setYPos(float p_y) {
	mPosY = p_y;
}

float Player::getCenterX() {
	return mPosX + (width / 2);
}
float Player::getCenterY() {
	return mPosY + (height / 2);
}

float Player::getHeight() {
	return height;
}

float Player::getWidth() {
	return width;
}

int Player::returnMovementDirection() {
	if (left) {
		return 0;
	}
	if (right) {
		return 2;
	}
	if (up) {
		return 3;
	}
	if (down) {
		return 1;
	}
	return 1;
}

int Player::getAttackDir() {
	return attackDir;
}

SDL_Rect* Player::getHitbox() {
	return &hitbox;
}
