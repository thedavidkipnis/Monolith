#include "Entity.h"

Entity::Entity(int w, int h, float posX, float posY) {
	width = w;
	height = h;
	mPosX = posX;
	mPosY = posY;

	MAX_VEL = 2;

	mVelX = 0;
	mVelY = 0;

	last_known_up = 0;
	last_known_down = 1000;
	last_known_left = 0;
	last_known_right = 1000;

	acceleration_factor = 2.0;
	decceleration_factor = 8.0;

	hitbox = {};
	hitbox.h = height;
	hitbox.w = width;
	hitbox.x = mPosX;
	hitbox.y = mPosY;
}

int Entity::checkCollision(SDL_Rect a, SDL_Rect b) {
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
		if (bottom_a >= bottom_b && !(a_center_x >= left_b - (a.w / 2) - 5 && a_center_x <= left_b - (a.w / 2) + 5)) {
			last_known_up = bottom_b + 1;
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
			last_known_up = bottom_b + 1;
			return 3;
		}
		else if (top_a <= top_b && !(a_center_x >= right_b + (a.w / 2) - 5 && a_center_x <= right_b + (a.w / 2) + 5)) {
			last_known_down = top_b;
			return 1;
		}
		else {
			last_known_left = right_b + 1;
			return 2;
		}
	}
}


void Entity::chasePlayer(float playerX, float playerY, std::vector<SDL_Rect> barriers) {
	float distToPlayer = distanceToPoint(playerX, playerY);

	for (int i = 0; i < barriers.size(); i++) {
		int collisionCheck = checkCollision(hitbox, barriers[i]);
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

	if (getCenterX() < playerX && distToPlayer < 500) {
		// accelerate right
		if ((mVelX / 100) < MAX_VEL) {
			mVelX += acceleration_factor;
		}
	}
	else if (mVelX > 0) {
		if (abs(mVelX) < decceleration_factor) {
			mVelX = 0;
		}
		else {
			mVelX -= decceleration_factor;
		}
	}

	if (getCenterX() > playerX && distToPlayer < 500) {
		// accelerate left
		if ((mVelX / 100) > -MAX_VEL) {
			mVelX -= acceleration_factor;
		}	
	} 
	else if (mVelX < 0) {
		if (abs(mVelX) < decceleration_factor) {
			mVelX = 0;
		}
		else {
			mVelX += decceleration_factor;
		}
	}

	if (getCenterY() < playerY && distToPlayer < 500) {
		if ((mVelY / 100) < MAX_VEL) {
			mVelY += acceleration_factor;
		}
	}
	else if (mVelY > 0) {
		if (abs(mVelY) < decceleration_factor) {
			mVelY = 0;
		}
		else {
			mVelY -= decceleration_factor;
		}
	}

	if(getCenterY() > playerY && distToPlayer < 500) {
		if ((mVelY / 100) > -MAX_VEL) {
			mVelY -= acceleration_factor;
		}
	}
	else if (mVelY < 0) {
		if (abs(mVelY) < decceleration_factor) {
			mVelY = 0;
		}
		else {
			mVelY += decceleration_factor;
		}
	}

	mPosX += mVelX/100;
	mPosY += mVelY/100;

	hitbox.x = mPosX;
	hitbox.y = mPosY;
}

float Entity::getXPos() {
	return mPosX;
}
float Entity::getYPos() {
	return mPosY;
}
float Entity::getCenterX() {
	return mPosX + (width / 2);
}
float Entity::getCenterY() {
	return mPosY + (height / 2);
}
void Entity::setXPos(float p_x) {
	mPosX = p_x;
}
void Entity::setYPos(float p_y) {
	mPosY = p_y;
}

SDL_Rect* Entity::getHitbox() {
	return &hitbox;
}

float Entity::distanceToPoint(float x, float y) {
	return sqrt(pow(getCenterX() - x, 2) + pow(getCenterY() - y,2));
}
