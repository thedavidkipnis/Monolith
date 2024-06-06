/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

TILE Class Header

Represents a tile in a Room object, i.e. one basic unit on the Room floor

*/

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

