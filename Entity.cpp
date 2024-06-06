/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

ENTITY Class

Non-player entities in the game, both hostile and non-hostile

*/

#pragma once
#include <Entity.h>

Entity::Entity(int w, int h, float posX, float posY) {
	width = w;
	height = h;
	mPosX = posX;
	mPosY = posY;

	MAX_VEL = 2;

	mVelX = 0;
	mVelY = 0;

	acceleration_factor = 2.0;
	decceleration_factor = 8.0;

	hitbox = {};
	hitbox.h = height;
	hitbox.w = width;
	hitbox.x = mPosX;
	hitbox.y = mPosY;
}


void Entity::chasePlayer(float playerX, float playerY, std::vector<Tile> * barriers) {

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

	// checking distance to player
	float distToPlayer = distanceToPoint(playerX, playerY);

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
