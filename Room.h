/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

ROOM Class Header

Represents a Room object, with its tile, barriers, and entities

*/

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

	// basic room generation - used for testing
	Room();

	// generate room object using a room config file from /rooms
	Room(string file_name);

	//non collision tiles
	std::vector<Tile>* getTiles();

	//collidable, 'barrier' tiles - used in checking collision
	std::vector<Tile>* getBarriers();

	/* 
	* returns neighbor if exists based on the following	 
	* 0 = left neighbor
	* 1 = top neighbor
	* 2 = right neighbor
	* 3 = bottom neighbor
	* 
	* returns NULL if neighbor doesn't exist
	*/
	Room* getNeighborAt(int position);

	std::vector<Room*>* getNeighbors();

	// sets neighbor at specified     neighbor position
	void setNeighborAt(int position, Room* neighbor);


private:

	/*
	* Helper function for parsing room configuration files
	* 
	* Returns comma separated string, each integer representing tile ID for that position
	*/
	string parseRoomFile(string filepath);

	std::vector<Tile> tiles;
	std::vector<Tile> barriers;

	std::vector<Room*> neighbors;

};

