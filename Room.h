#pragma once

#include <SDL.h>
#include <Entity.h>
#include <Tile.h>
#include <vector>

class Room
{
public:
	Room();

	std::vector<Tile>* getTiles();
	std::vector<Tile>* getBarriers();

	Room* getNeighborAt(int position);

private:
	std::vector<Tile> tiles;
	std::vector<Tile> barriers;

	std::vector<Room*> neighbors;

};

