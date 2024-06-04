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

	last_known_up = 0;
	last_known_down = 1000;
	last_known_left = 0;
	last_known_right = 1000;

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

int Player::checkCollision(SDL_Rect a, SDL_Rect b) {
	int left_a, left_b, right_a, right_b;
	int top_a, top_b, bottom_a, bottom_b;

	int a_center_x = a.x + (a.w / 2);
	int a_center_y = a.y + (a.h / 2);
	int b_center_x = b.x + (b.w / 2);
	int b_center_y = b.y + (b.h / 2);

	left_a = a.x;
	right_a = a.x + a.w;
	top_a = a.y;
	bottom_a = a.y + a.h;

	left_b = b.x;
	right_b = b.x + b.w;
	top_b = b.y;
	bottom_b = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottom_a <= top_b || top_a >= bottom_b || right_a <= left_b || left_a >= right_b)
	{
		return -1;
	}

	if ((a_center_x <= b_center_x)) {
		if (bottom_a >= bottom_b && !(a_center_x >= left_b - (a.w/2) - 5 && a_center_x <= left_b - (a.w / 2) + 5)) {
			last_known_up = bottom_b+1;
			return 3;
		}
		else if (top_a <= top_b && !(a_center_x >= left_b - (a.w / 2) - 5 && a_center_x <= left_b - (a.w / 2) + 5)) {
			last_known_down = top_b;
			return 1;
		}
		else {
			last_known_right = left_b;
			return 0;
		}
	}
	else {
		if (bottom_a >= bottom_b && !(a_center_x >= right_b + (a.w / 2) - 5 && a_center_x <= right_b + (a.w / 2) + 5)) {
			last_known_up = bottom_b+1;
			return 3;
		}
		else if (top_a <= top_b && !(a_center_x >= right_b + (a.w / 2) - 5 && a_center_x <= right_b + (a.w / 2) + 5)) {
			last_known_down = top_b;
			return 1;
		}
		else {
			last_known_left = right_b+1;
			return 2;
		}
	}
}

void Player::move(float screenWidth, float screenHeight, std::vector<Tile> * barriers) {

	for (int i = 0; i < barriers->size(); i++) {
		int collisionCheck = checkCollision(hitbox, barriers->at(i).getTile());
		if (collisionCheck >= 0) {
			switch (collisionCheck) {
			case 0:
				mPosX = last_known_right - width;
				mVelX = 0;
				break;
			case 1:
				mPosY = last_known_down - height;
				mVelY = 0;
				break;
			case 2:
				mPosX = last_known_left;
				mVelX = 0;
				break;
			case 3:
				mPosY = last_known_up;
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

int Player::returnDirection() {
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