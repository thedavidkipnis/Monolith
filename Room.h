#pragma once

#include <SDL.h>
#include <Entity.h>
#include <Tile.h>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <iostream>
#include <print>

using namespace std;

class Room
{
public:
	Room();

	Room(string file_name);

	std::vector<Tile>* getTiles();
	std::vector<Tile>* getBarriers();

	Room* getNeighborAt(int position);
	void setNeighborAt(int position, Room* neighbor);


private:

	string parseRoomFile(string file_name);

	std::vector<Tile> tiles;
	std::vector<Tile> barriers;

	std::vector<Room*> neighbors;

};

