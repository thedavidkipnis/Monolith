#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <Player.h>
#include <Entity.h>
#include <Sprite.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>

class Game
{
public:
	Game();

	//Screen dimension constants
	const float SCREEN_WIDTH = 640 * 2;
	const float SCREEN_HEIGHT = 480 * 2;

	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();

	//Frees media and shuts down SDL
	void close();

	void render_player(int dir, float w, float h, float mPosX, float mPosY);
	void render_tile(Sprite* texture, float mPosX, float mPosY, float width, float height, double angle);

	int run();

private:

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//Scene textures
	Sprite gBlockTexture;
	Sprite dirtTexture;
	Sprite spooderTexture;
	Sprite doorTexture;

	Sprite swordTexture;

	Sprite p_up;
	Sprite p_down;
	Sprite p_left;
	Sprite p_right;


	int attackDir = -1;


};

