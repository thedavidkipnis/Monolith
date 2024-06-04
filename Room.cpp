#include "Room.h"
#include <time.h>

Room::Room() {

	tiles.reserve(192);
	barriers.reserve(192);

	srand(time(0));
	for (size_t i = 0; i < 16; i++)
	{
		for (size_t j = 0; j < 12; j++)
		{
			SDL_Rect tileRect{ i * 80, j * 80, 80, 80 };

			if (i == 0 || i == 15 || j == 0 || j == 11 || (i == 5 && j == 7)) {
				Tile newTile = Tile::Tile(1, tileRect);
				barriers.push_back(newTile);
			}
			else {
				Tile newTile = Tile::Tile(0, tileRect);
				tiles.push_back(newTile);
			}
		}
	}

}

std::vector<Tile>* Room::getTiles() {
	return &tiles;
}

std::vector<Tile>* Room::getBarriers() {
	return &barriers;
}

Room* Room::getNeighborAt(int position) {
	return neighbors[position];
}
