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

class MathFunc
{
public:
	static int checkCollision(SDL_Rect a, SDL_Rect b);
};

