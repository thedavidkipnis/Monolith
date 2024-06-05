#include "Room.h"

using namespace std;

Room::Room() {

	tiles.reserve(192);
	barriers.reserve(192);

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

string Room::parseRoomFile(string file_name) {
	ifstream roomfile;
	roomfile.exceptions(ifstream::badbit | ifstream::failbit);

	string room_config = "";

	try {
		roomfile.open(file_name);

		string t;
		while (getline(roomfile, t)) {
			room_config.append(t);
		}

		roomfile.close();
		return room_config;
	}
	catch (ifstream::failure& e) {
		printf("%s %s\n", "Failed to open room file:", file_name.c_str());
		printf("%s\n", e.what());
	}

	return room_config;
}

Room::Room(string file_name) {

	tiles.reserve(192);
	barriers.reserve(192);
	neighbors.reserve(4);

	for (size_t i = 0; i < 4; i++)
	{
		neighbors.push_back(nullptr);
	}

	string config = parseRoomFile(file_name);
	int counter = 0;
	int column_counter = 0;
	int row_counter = 0;

	for (char c : config) {
		if (c != ',') {

			row_counter = counter / 12;
			column_counter = counter % 12;

			SDL_Rect tileRect{ row_counter * 80, column_counter * 80, 80, 80 };

			switch (c) {
			case '0':
			{
				Tile newTile = Tile::Tile(0, tileRect);
				tiles.push_back(newTile);
			}
				break;
			case '1':
			{
				Tile newTile = Tile::Tile(1, tileRect);
				barriers.push_back(newTile);
			}
				break;
			}

			counter++;
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

void Room::setNeighborAt(int position, Room* neighbor) {
	neighbors[position] = neighbor;
}
