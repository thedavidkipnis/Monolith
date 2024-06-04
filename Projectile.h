#pragma once
class Projectile
{
public:

	Projectile(int w, int h, float posX, float posY);

	float getY();
	void setY(float y);
	float getX();
	void setX(float x);

	float getHeight();
	void setHeight(float h);
	float getWidth();
	void setWidth(float w);

	float getSpeed();
	void setSpeed(float sp);

	int getDirection();
	void setDirection(int dir);
	
private:
	float x, y;
	float width, height;
	float speed;

	int direction;
};

