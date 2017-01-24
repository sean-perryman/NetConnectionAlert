/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "/usr/local/Cellar/sdl2/2.0.3/include/SDL2/SDL.h"
#include "/usr/local/Cellar/sdl2_image/2.0.1_1/include/SDL2/SDL_image.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include "/usr/local/opt/curl/include/curl/curl.h"

//Screen dimension constants
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 320;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gStatus = NULL;

//Boolean to store game status
bool gameRunning = true;
SDL_Event event;

//Texture rotation stuff
double angle;
SDL_Texture* texture;
SDL_Rect rect;
SDL_Point center;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gStatus = IMG_Load( "status.png" );
	if( gStatus == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "status.png", SDL_GetError() );
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface( gStatus );
	gStatus = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void LoadTexture( SDL_Renderer *renderer, const std::string &str, const SDL_Rect &windowRect )
{
		SDL_Surface* surface = IMG_Load( str.c_str() );
		texture = SDL_CreateTextureFromSurface( renderer, surface );
		SDL_FreeSurface( surface );
		//SetInitialPosition( windowRect );
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Apply the image
			SDL_BlitSurface( gStatus, NULL, gScreenSurface, NULL );
			
			//Update the surface
			SDL_UpdateWindowSurface( gWindow );

			//Game Loo
			
			while (gameRunning) {
				//Do things here
				if (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						gameRunning = false;
					}
				} 
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
