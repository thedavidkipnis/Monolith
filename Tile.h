#pragma once

#include <SDL.h>

class Tile
{
public:
	Tile(int ID, SDL_Rect new_tile);

	int getTileID();
	void setTileID(int id);

	SDL_Rect getTile();
	void setTile(SDL_Rect new_tile);

private:
	int tileID;
	SDL_Rect tile;
};

