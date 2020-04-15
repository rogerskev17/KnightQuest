#include "game.h"

void exit(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Joystick*& gameController)
{
	SDL_JoystickClose(gameController);
	gameController = nullptr;

	SDL_DestroyRenderer(renderer);
	window = nullptr;

	SDL_DestroyWindow(window);
	renderer = nullptr;

	IMG_Quit();
	SDL_Quit();
}
