#include "game.h"
#include "worlds.h"

//World 1

//Constructor
World1::World1(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer*& renderer)
{
	window_width = SCREEN_WIDTH;
	window_height = SCREEN_HEIGHT;

	pSpriteSheet = IMG_LoadTexture(renderer, "male_base-test-anim.gif");


	if (pSpriteSheet == nullptr)
	{
		cout << "Unable to load player Sprite sheet.";
	}

	//facing down sprite
	pSpriteClips[0].x = 14;
	pSpriteClips[0].y = 12;
	pSpriteClips[0].w = 145;
	pSpriteClips[0].h = 320;


	//facing left/right sprite
	pSpriteClips[1].x = 385;
	pSpriteClips[1].y = 5;
	pSpriteClips[1].w = 136;
	pSpriteClips[1].h = 325;

	//facing up sprite
	pSpriteClips[2].x = 770;
	pSpriteClips[2].y = 5;
	pSpriteClips[2].w = 172;
	pSpriteClips[2].h = 330;

	//current player sprite- starts off facing down
	pSprite = pSpriteClips[0];

	//player sprite rectangle
	pBase.x = 0;
	pBase.y = 0;
	pBase.w = pSpriteClips[0].w;
	pBase.h = pSpriteClips[0].h;
}

//Destructor- Be sure to fix memory leaks
World1::~World1()
{
	if (pSpriteSheet != nullptr)
	{
		SDL_DestroyTexture(pSpriteSheet);
		pSpriteSheet = nullptr;
	}
}

void World1::renderMap(SDL_Renderer*& renderer)
{
	SDL_RenderClear(renderer); //clears screen
	SDL_RenderCopy(renderer, gWorld, NULL, NULL);
}

//renders player to screen
void World1::renderPlayer(SDL_Renderer*& renderer)
{
	//Prepare Sprite sheet for rendering
	pBase.x = static_cast<int>(pPosX);
	pBase.y = static_cast<int>(pPosY);

	//render
	SDL_RenderCopyEx(renderer, pSpriteSheet, &pSprite, &pBase, 0.0, NULL, sFlip);
	SDL_RenderPresent(renderer); //puts image on screen
}

//event handling
void World1::handlePlayerEvents(SDL_Joystick*& controller)
{

	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			gQuit = true;
		}


		//handles movement with collisions at end of the screen
		this->keyboardMovePlayerEvent();
		this->controllerMovePlayerEvent();
	}
}

//moves player
void World1::keyboardMovePlayerEvent()
{
	//keyboard movement support with end of screen collisions
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
			//up
		case SDLK_UP:
			pVelY = -PLAYER_VELOCITY_Y;
			sFlip = SDL_FLIP_NONE;
			pSprite = pSpriteClips[2];
			break;

			//down
		case SDLK_DOWN:
			pVelY = PLAYER_VELOCITY_Y;
			sFlip = SDL_FLIP_NONE;
			pSprite = pSpriteClips[0];
			break;

			//left
		case SDLK_LEFT:
			pVelX = -PLAYER_VELOCITY_X;
			sFlip = SDL_FLIP_HORIZONTAL;
			pSprite = pSpriteClips[1];
			break;

			//right
		case SDLK_RIGHT:
			pVelX = PLAYER_VELOCITY_X;
			sFlip = SDL_FLIP_NONE;
			pSprite = pSpriteClips[1];
			break;

		default:
			break;
		}
	}

	//keyboard movement support continued
	else if (e.type == SDL_KEYUP)
	{

		switch (e.key.keysym.sym)
		{
			//up
		case SDLK_UP:
		{
			pVelY = 0;
			break;
		}

		//down
		case SDLK_DOWN:
		{
			pVelY = 0;
			break;
		}

		//left
		case SDLK_LEFT:
		{
			pVelX = 0;
			break;
		}

		//right
		case SDLK_RIGHT:
		{
			pVelX = 0;
			break;
		}

		default:
			break;
		}
	}
}

//controller movement support
void World1::controllerMovePlayerEvent()
{
	if (e.type == SDL_JOYAXISMOTION)
	{
		if (e.jaxis.which == 0)//controller 0
		{
			if (e.jaxis.axis == 0) // x axis
			{
				//left
				if (e.jaxis.value < -CONTROLLER_DEAD_ZONE)
				{
					pVelX = -PLAYER_VELOCITY_X;
					sFlip = SDL_FLIP_HORIZONTAL;
					pSprite = pSpriteClips[1];
				}

				//right
				else if (e.jaxis.value > CONTROLLER_DEAD_ZONE)
				{
					pVelX = PLAYER_VELOCITY_X;
					sFlip = SDL_FLIP_NONE;
					pSprite = pSpriteClips[1];
				}

				else
				{
					pVelX = 0;
				}
			}

			else if (e.jaxis.axis == 1) //y axis
			{
				//up
				if (e.jaxis.value < -CONTROLLER_DEAD_ZONE)
				{
					pVelY = -PLAYER_VELOCITY_Y;
					sFlip = SDL_FLIP_NONE;
					pSprite = pSpriteClips[2];
				}

				//down
				else if (e.jaxis.value > CONTROLLER_DEAD_ZONE)
				{
					pVelY = PLAYER_VELOCITY_Y;
					sFlip = SDL_FLIP_NONE;
					pSprite = pSpriteClips[0];
				}

				else
				{
					pVelY = 0;
				}
			}
		}
	}
}

//moves player
void World1::movePlayer()
{
	//update x and collision check
	pPosX += pVelX;
	if (pPosX < 0 || (pPosX + pBase.w > window_width))
	{
		pPosX -= pVelX;
	}

	//update y and collision check
	pPosY += pVelY;
	if (pPosY < 0 || (pPosY + pBase.h > window_height))
	{
		pPosY -= pVelY;
	}
}

//main loop of program
void World1::mainLoop(SDL_Renderer*& renderer, SDL_Joystick*& controller)
{
	gQuit = false; // flag for main loop

	while (!gQuit) //check for game exit
	{
		//player input
		this->handlePlayerEvents(controller);

		//update game internals
		this->movePlayer();


		//update display
		this->renderMap(renderer);
		this->renderPlayer(renderer);
	}
}

//End world 1
