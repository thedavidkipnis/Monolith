/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

MATHFUNC Class

Helper class that contains mathematical functions for performing game physics calculations

*/

#include "MathFunc.h"

int MathFunc::checkCollision(SDL_Rect a, SDL_Rect b) {
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
			//last_known_up = bottom_b + 1;
			return 3;
		}
		else if (top_a <= top_b && !(a_center_x >= left_b - (a.w / 2) - 5 && a_center_x <= left_b - (a.w / 2) + 5)) {
			//last_known_down = top_b;
			return 1;
		}
		else {
			//last_known_right = left_b;
			return 0;
		}
	}
	else {
		if (bottom_a >= bottom_b && !(a_center_x >= right_b + (a.w / 2) - 5 && a_center_x <= right_b + (a.w / 2) + 5)) {
			//last_known_up = bottom_b + 1;
			return 3;
		}
		else if (top_a <= top_b && !(a_center_x >= right_b + (a.w / 2) - 5 && a_center_x <= right_b + (a.w / 2) + 5)) {
			//last_known_down = top_b;
			return 1;
		}
		else {
			//last_known_left = right_b + 1;
			return 2;
		}
	}
}
