/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

MATHFUNC Class Header

Helper class that contains mathematical functions for performing game physics calculations

*/

#pragma once

#include <SDL.h>
#include <Circle.h>

class MathFunc
{
public:

	/* returns the direction from which a is colliding with b, and -1 if there is no collision
	* 0 = from left
	* 1 = from top
	* 2 = from right
	* 3 = from bottom
	*/ 
	static int checkCollision(SDL_Rect a, SDL_Rect b);
	static bool checkCollision(Circle a, SDL_Rect b);
	static double distanceSquared(int x1, int y1, int x2, int y2);
};

