/*
Copyright KD Studios
Written by David Kipnis, 2024
*/

/*

GAME Class Header

Main Game object that runs the game

*/

#pragma once

#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <Player.h>
#include <Entity.h>
#include <Sprite.h>
#include <Room.h>  
#include <Tile.h>
#include <Object.h>


class Game
{
public:
	Game();

	//Screen dimension constants
	const float SCREEN_WIDTH = 640 * 2;
	const float SCREEN_HEIGHT = 480 * 2;

	/* 
	* Starts up SDL and creates window
	* SDL Tutorial function
	*/
	bool init();

	/*
	* Load media files (all the PNGs :D)
	* SDL Tutorial function
	*/
	bool loadMedia();

	/*
	* Frees media and shuts down SDL
	* SDL Tutorial function
	*/
	void close();

	// renders player sprite
	void renderPlayer(Player* player);

	/*
	* renders tile sprite
	* texture = texture for the tile
	* posX, posY = coordinates for sprite
	* width, height = dimensions for character's sprite
	* angle = how much the texture is rotated
	*/
	void renderTile(Sprite* texture, float posX, float posY, float width, float height, double angle);

	// renders current room
	void renderRoom(std::vector<Tile>* tiles, std::vector<Tile>* barriers, std::vector<Room*>* neighbors);

	// checks if player is in a doorway to another room
	Room* isPlayerInDoorway(Room* curRoom, float player_x, float player_y);

	//moves player into new room and changes room tiles, barriers and entities
	void moveToRoom(Player* player, Room* newRoom);

	// main game run time loop
	int run();

private:

	//window being rendered to
	SDL_Window* gWindow = NULL;

	//renderer being used
	SDL_Renderer* gRenderer = NULL;

	//room the game is currently in
	Room* curRoom;
	std::vector<Tile>* tiles;
	std::vector<Tile>* barriers;
	std::vector<Room*>* neighbors;

	//textures
	Sprite gBlockTexture;
	Sprite dirtTexture;
	Sprite spooderTexture;
	Sprite doorTexture;

	Sprite barrelTexture;
	Sprite coinTexture;

	Sprite swordTexture;

	//player directional textures
	Sprite p_up;
	Sprite p_down;
	Sprite p_left;
	Sprite p_right;


	int attackDir = -1;

};

