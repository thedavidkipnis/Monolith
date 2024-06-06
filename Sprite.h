/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

SPRITE Class Header

A sprite that can be rendered on the screen

*/

#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class Sprite
{
public:

	Sprite();

	//Memory deallocation
	~Sprite();

	//Loads image from file path
	bool loadFromFile(SDL_Renderer* renderer, std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

