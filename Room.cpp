/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

ROOM Class

Represents a Room object, with its tile, barriers, and entities

*/

#include "Room.h"

using namespace std;

Room::Room() {
	// currently empty cuz I don't need to use it lol
}

string Room::parseRoomFile(string filepath) {
	ifstream roomfile;
	roomfile.exceptions(ifstream::badbit | ifstream::failbit);

	string room_config = "";

	try {
		roomfile.open(filepath);

		// concatenating each line from file to final string
		string t;
		while (getline(roomfile, t)) {
			room_config.append(t);
		}

		roomfile.close();
	}
	catch (ifstream::failure& e) {
		printf("%s %s\n", "Failed to open room file:", filepath.c_str());
		printf("%s\n", e.what());
	}

	return room_config;
}

Room::Room(string file_name, int ID, int type) {

	roomID = ID;
	roomType = type;

	tiles.reserve(192);
	barriers.reserve(192);
	neighbors.reserve(4);

	// initializing neighbors with null ptrs
	for (size_t i = 0; i < 4; i++)
	{
		neighbors.push_back(nullptr);
	}

	/* The dimensions and tile counts are currently hardcoded
	* Will need to eventually refactor to address screen dimensions
	*/

	string config = parseRoomFile(file_name);
	int counter = 0;
	int column_counter = 0;
	int row_counter = 0;

	// parsing config string and populating room with tiles/barriers
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

int Room::getRoomID() {
	return roomID;
}

int Room::getRoomType() {
	return roomType;
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

std::vector<Room*>* Room::getNeighbors() {
	return &neighbors;
}

void Room::setNeighborAt(int position, Room* neighbor) {
	neighbors[position] = neighbor;
}
