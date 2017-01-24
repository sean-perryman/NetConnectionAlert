// Code sample from https://bitbucket.org/dandago/gigilabs/src/e2d13fc3664860b0d90759a036f41ed18db81223/Sdl2DisplayImage/Sdl2DisplayImage/main.cpp?at=master&fileviewer=file-view-default

//Using SDL and standard IO
#include "/usr/local/Cellar/sdl2/2.0.3/include/SDL2/SDL.h"
#include "/usr/local/Cellar/sdl2_image/2.0.1_1/include/SDL2/SDL_image.h"
#include "/usr/local/opt/curl/include/curl/curl.h"

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 320, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface * image = IMG_Load("status.png");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
		}

		SDL_Rect dstrect = { 0, 0, 320, 320 };
		SDL_RenderCopyEx(renderer, texture, NULL, &dstrect, 30, NULL, SDL_FLIP_NONE);
		//SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}