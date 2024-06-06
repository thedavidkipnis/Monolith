/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

TILE Class

Represents a tile in a Room object, i.e. one basic unit on the Room floor

*/


#include "Tile.h"

Tile::Tile(int ID, SDL_Rect new_tile) {
	tileID = ID;
	tile = new_tile;
}

// Getters, Setters
int Tile::getTileID() { return tileID; }
void Tile::setTileID(int id) { tileID = id; }

SDL_Rect Tile::getTile() { return tile; }
void Tile::setTile(SDL_Rect new_tile) { tile = new_tile; }

