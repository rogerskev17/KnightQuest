#include "game.h"

//Initialize SDL
void init(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Joystick*& gameController, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	//load SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("\nSDL was unable to initialize. SDL Error: %s\n", SDL_GetError());
	}

	//make window
	window = SDL_CreateWindow("Knight Quest v0.5", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("\nUnable to create window. SDL Error: %s\n", SDL_GetError());
	}

	//make renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("\nUnable to create renderer. SDL Error: %s\n", SDL_GetError());
	}
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

	//check for controller
	if (SDL_NumJoysticks() < 1)
	{
		cout << "\nNo controller connected.\n";
	}

	//load controller
	gameController = SDL_JoystickOpen(0);
	if (gameController == NULL)
	{
		cout << "\nUnable to open game controller. SDL Error: " << SDL_GetError() << "\n";
	}
}
//END OF SDL INIT
