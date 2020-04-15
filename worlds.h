#ifndef WORLDS_H_INCLUDED
#define WORLDS_H_INCLUDED

#include "game.h"

class World1
{
public:
	World1(int, int, SDL_Renderer*&); //passes in screen resolution
	~World1(); //destroys textures (may add own functions later)

			   //constants
	static constexpr float PLAYER_VELOCITY_X = 0.5; //x speed
	static constexpr float PLAYER_VELOCITY_Y = 0.5; //y speed
	static const int CONTROLLER_DEAD_ZONE = 20000; //dead zone for controller

												   //screen resolution
	int window_width = 0;
	int window_height = 0;

	//handles player
	void renderPlayer(SDL_Renderer*&);
	void handlePlayerEvents(SDL_Joystick*&);
	void keyboardMovePlayerEvent();
	void controllerMovePlayerEvent();
	void movePlayer();

	//main loop
	void mainLoop(SDL_Renderer*&, SDL_Joystick*&);

private:

	//world map
	SDL_Texture* gWorld;
	void renderMap(SDL_Renderer*&);

	//player graphic and rectangle structs/variables/etc.
	SDL_Texture* pSpriteSheet = nullptr;
	SDL_Rect pSpriteClips[3];
	SDL_Rect pSprite;
	SDL_Rect pBase;
	SDL_RendererFlip sFlip = SDL_FLIP_NONE;

	//player movement and velocity
	float pVelX = 0;
	float pVelY = 0;
	float pPosX = 0;
	float pPosY = 0;

	SDL_Event e; // event handler variable
	bool gQuit = false; // quit event flag
};

#endif // WORLDS_H_INCLUDED
