#include "game.h"

void init(SDL_Window*&, SDL_Renderer*&, SDL_Joystick*&, int, int);
void exit(SDL_Window*&, SDL_Renderer*&, SDL_Joystick*&);

int main(int argc, char* argv[])
{
    //screen resolution (allow user to modify later)
	static const int SCREEN_WIDTH = 1024;
	static const int SCREEN_HEIGHT = 768;

	SDL_Window* window = NULL; //make window
	SDL_Renderer* renderer = NULL;// make renderer
	SDL_Joystick* gameController = NULL; //make controller

    //initialize SDL 2
	init(window, renderer, gameController, SCREEN_WIDTH, SCREEN_HEIGHT);

	//World Loader
	World1 world(SCREEN_WIDTH, SCREEN_HEIGHT, renderer);

	world.mainLoop(renderer, gameController);

	//exit SDL 2 and end program
	exit(window, renderer, gameController);

    return 0;
}
