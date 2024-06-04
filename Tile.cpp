#include "Tile.h"

Tile::Tile(int ID, SDL_Rect new_tile) {
	tileID = ID;
	tile = new_tile;
}

int Tile::getTileID() { return tileID; }
void Tile::setTileID(int id) { tileID = id; }

SDL_Rect Tile::getTile() { return tile; }
void Tile::setTile(SDL_Rect new_tile) { tile = new_tile; }

