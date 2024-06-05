#include "Game.h"

Game::Game() {

}

void Game::render_player(int dir, float w, float h, float mPosX, float mPosY)
{
	switch (dir) {
	case 0:
		p_left.render(gRenderer, mPosX, mPosY, h, w);
		break;
	case 1:
		p_up.render(gRenderer, mPosX, mPosY, h, w);
		break;
	case 2:
		p_right.render(gRenderer, mPosX, mPosY, h, w);
		break;
	default:
		p_down.render(gRenderer, mPosX, mPosY, h, w);
		break;
	}
}

void Game::render_tile(Sprite* texture, float mPosX, float mPosY, float width, float height, double angle) {
	texture->render(gRenderer, mPosX, mPosY, width, height, NULL, angle);
}

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;

	if (!gBlockTexture.loadFromFile(gRenderer, "img/Stone Wall.png"))
	{
		printf("Failed to load block texture!\n");
		success = false;
	}

	if (!dirtTexture.loadFromFile(gRenderer, "img/dirt.png"))
	{
		printf("Failed to load dirt texture!\n");
		success = false; 
	}
	if (!spooderTexture.loadFromFile(gRenderer, "img/spood.png"))
	{
		printf("Failed to load spood texture!\n");
		success = false;
	}

	if (!doorTexture.loadFromFile(gRenderer, "img/door.png"))
	{
		printf("Failed to load door texture!\n");
		success = false;
	}

	if (!swordTexture.loadFromFile(gRenderer, "img/sword.png"))
	{
		printf("Failed to load sword texture!\n");
		success = false;
	}


	if (!p_up.loadFromFile(gRenderer, "img/k_down.png"))
	{
		printf("Failed to load k_down texture!\n");
		success = false;
	}
	if (!p_down.loadFromFile(gRenderer, "img/k_up.png"))
	{
		printf("Failed to load k_up texture!\n");
		success = false;
	}
	if (!p_left.loadFromFile(gRenderer, "img/k_left.png"))
	{
		printf("Failed to load k_left texture!\n");
		success = false;
	}
	if (!p_right.loadFromFile(gRenderer, "img/k_right.png"))
	{
		printf("Failed to load k_right texture!\n");
		success = false;
	}

	return success;
}

void Game::close()
{
	//Free loaded images
	p_down.free();
	p_up.free();
	p_left.free();
	p_right.free();

	gBlockTexture.free();
	dirtTexture.free();
	spooderTexture.free();
	doorTexture.free();
	swordTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int Game::run()
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
		return -1;
	}

	//Load media
	if (!loadMedia())
	{
		printf("Failed to load media!\n");
		return -1;
	}

	srand(time(0));

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	Player* player = new Player(75, 75, 100, 100);
	//Entity* testSpooder = new Entity(75, 75, 1000, 800);


	// generating rooms
	Room room1 = Room::Room("rooms/empty_test_1.txt");
	Room room2 = Room::Room("rooms/empty_test_2.txt");
	Room room3 = Room::Room("rooms/empty_test_3.txt");
	Room room4 = Room::Room("rooms/empty_test_3.txt");
	Room room5 = Room::Room("rooms/empty_test_3.txt");

	room1.setNeighborAt(0, &room2);
	room2.setNeighborAt(2, &room1);

	room2.setNeighborAt(0, &room5);
	room5.setNeighborAt(2, &room2);

	room1.setNeighborAt(1, &room3);
	room3.setNeighborAt(3, &room1);

	room1.setNeighborAt(3, &room4);
	room4.setNeighborAt(1, &room1);

	Room* curRoom = &room1;

	std::vector<Tile>* tiles = curRoom->getTiles();
	std::vector<Tile>* barriers = curRoom->getBarriers();

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			//Handle input for the dot
			player->handleEvent(e);
			player->attack(e);
		}

		//Move the dot
		player->move(SCREEN_WIDTH, SCREEN_HEIGHT, barriers);
		//testSpooder->chasePlayer(player->getCenterX(), player->getCenterY(), barriers);

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//renders all non barrier tiles
		for (size_t i = 0; i < tiles->size(); i++)
		{
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0xFF, 0xFF);
			render_tile(&dirtTexture, tiles->at(i).getTile().x, tiles->at(i).getTile().y, 80, 80, 0);
		}
		//renders all barriers
		for (size_t i = 0; i < barriers->size(); i++)
		{
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0xFF, 0xFF);
			render_tile(&gBlockTexture, barriers->at(i).getTile().x, barriers->at(i).getTile().y, 80, 80, 0);
		}

		render_player(player->returnDirection(),
			player->getHeight(),
			player->getWidth(),
			player->getXPos(),
			player->getYPos());
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0x00);
		SDL_RenderDrawRect(gRenderer, player->getHitbox());

		/*render_tile(&spooderTexture, testSpooder->getXPos(), testSpooder->getYPos(), 75, 75, 0);
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0x00);
		SDL_RenderDrawRect(gRenderer, testSpooder->getHitbox());*/

		if (curRoom->getNeighborAt(0) != NULL) {
			render_tile(&doorTexture, -40, 440, 160, 80, 270);
		}

		if (curRoom->getNeighborAt(1) != NULL) {
			render_tile(&doorTexture, 560, 0, 160, 80, 0);
		}

		if (curRoom->getNeighborAt(2) != NULL) {
			render_tile(&doorTexture, 1160, 440, 160, 80, 90);
		}

		if (curRoom->getNeighborAt(3) != NULL) {
			render_tile(&doorTexture, 560, 880, 160, 80, 180);
		}

		int attackDirection = player->getAttackDir();
		if (attackDirection > -1) {
			switch (attackDirection) {
			case(0):
				render_tile(&swordTexture, player->getCenterX() - 80, player->getCenterY() - 32, 64, 64, 270);
				break;
			case(1):
				render_tile(&swordTexture, player->getCenterX() - 32, player->getCenterY() - 80, 64, 64, 0);
				break;
			case(2):
				render_tile(&swordTexture, player->getCenterX() + 16, player->getCenterY() - 32, 64, 64, 90);
				break;
			case(3):
				render_tile(&swordTexture, player->getCenterX() - 32, player->getCenterY() + 16, 64, 64, 180);
				break;
			}
		}

		//Update screen
		SDL_RenderPresent(gRenderer);

		float px = player->getXPos();
		float py = player->getYPos();

		if (px >= 580 && px <= 700 && py <= 80 and curRoom->getNeighborAt(1) != NULL) {
			curRoom = curRoom->getNeighborAt(1);
			barriers = curRoom->getBarriers();
			tiles = curRoom->getTiles();

			player->moveIntoRoom(3);
			printf("%s\n", "moved into top room");

		}
		if (px <= 81 && py >= 440 && py <= 520 and curRoom->getNeighborAt(0) != NULL) {
			curRoom = curRoom->getNeighborAt(0);
			barriers = curRoom->getBarriers();
			tiles = curRoom->getTiles();

			player->moveIntoRoom(2);
			printf("%s\n", "moved into left room");

		}
		if (px >= 1119 && py >= 440 && py <= 520 and curRoom->getNeighborAt(2) != NULL) {
			curRoom = curRoom->getNeighborAt(2);
			barriers = curRoom->getBarriers();
			tiles = curRoom->getTiles();

			player->moveIntoRoom(0);
			printf("%s\n", "moved into right room");

		}
		if (px >= 580 && px <= 700 && py >= 799 and curRoom->getNeighborAt(3) != NULL) {
			curRoom = curRoom->getNeighborAt(3);
			barriers = curRoom->getBarriers();
			tiles = curRoom->getTiles();

			player->moveIntoRoom(1);
			printf("%s\n", "moved into bottom room");

		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
