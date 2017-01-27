// Code sample from https://bitbucket.org/dandago/gigilabs/src/e2d13fc3664860b0d90759a036f41ed18db81223/Sdl2DisplayImage/Sdl2DisplayImage/main.cpp?at=master&fileviewer=file-view-default

//Using SDL and standard IO
#include "/usr/local/Cellar/sdl2/2.0.5/include/SDL2/SDL.h"
#include "/usr/local/Cellar/sdl2_image/2.0.1_1/include/SDL2/SDL_image.h"
#include "/usr/local/Cellar/sdl2/2.0.5/include/SDL2/SDL_audio.h"
#include "/usr/local/opt/curl/include/curl/curl.h"
#include <queue>
#include <cmath>

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) { return size * nmemb; }

//Init cURL stuff only once.
CURL *curl;
CURLcode res;

/* Being "beep" code from: http://stackoverflow.com/questions/10110905/simple-wave-generator-with-sdl-in-c */
const int AMPLITUDE = 28000;
const int FREQUENCY = 44100;

struct BeepObject
{
    double freq;
    int samplesLeft;
};

class Beeper
{
	private:
    double v;
    std::queue<BeepObject> beeps;
	public:
    Beeper();
    ~Beeper();
    void beep(double freq, int duration);
    void generateSamples(Sint16 *stream, int length);
    void wait();
};

void audio_callback(void*, Uint8*, int);

Beeper::Beeper()
{
  SDL_AudioSpec desiredSpec;

  desiredSpec.freq = FREQUENCY;
  desiredSpec.format = AUDIO_S16SYS;
  desiredSpec.channels = 1;
  desiredSpec.samples = 2048;
  desiredSpec.callback = audio_callback;
  desiredSpec.userdata = this;

  SDL_AudioSpec obtainedSpec;

  // you might want to look for errors here
  SDL_OpenAudio(&desiredSpec, &obtainedSpec);

  // start play audio
  SDL_PauseAudio(0);
}

Beeper::~Beeper()
{
  SDL_CloseAudio();
}

void Beeper::generateSamples(Sint16 *stream, int length)
{
  int i = 0;
  while (i < length) {

	  if (beeps.empty()) {
	      while (i < length) {
	          stream[i] = 0;
	          i++;
	      }
	      return;
	  }
	  BeepObject& bo = beeps.front();

	  int samplesToDo = std::min(i + bo.samplesLeft, length);
	  bo.samplesLeft -= samplesToDo - i;

	  while (i < samplesToDo) {
	      stream[i] = AMPLITUDE * std::sin(v * 2 * M_PI / FREQUENCY);
	      i++;
	      v += bo.freq;
	  }

	  if (bo.samplesLeft == 0) {
	      beeps.pop();
	  }
  }
}

void Beeper::beep(double freq, int duration)
{
    BeepObject bo;
    bo.freq = freq;
    bo.samplesLeft = duration * FREQUENCY / 1000;

    SDL_LockAudio();
    beeps.push(bo);
    SDL_UnlockAudio();
}

void Beeper::wait()
{
  int size;
  do {
      SDL_Delay(20);
      SDL_LockAudio();
      size = beeps.size();
      SDL_UnlockAudio();
  } while (size > 0);

}

void audio_callback(void *_beeper, Uint8 *_stream, int _length)
{
  Sint16 *stream = (Sint16*) _stream;
  int length = _length / 2;
  Beeper* beeper = (Beeper*) _beeper;

  beeper->generateSamples(stream, length);
}
/* end beep code */

bool ping() //From: https://curl.haxx.se/libcurl/c/simple.html
{
	curl = curl_easy_init();
  if(curl) {
  	curl_easy_setopt(curl, CURLOPT_URL, "http://google.com");
    
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
    {
      return false;
    }
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  return true;
}

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window * window = SDL_CreateWindow("Network Connection Alert",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 320, 0);

	//Display Texture Stuff
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface * image = IMG_Load("status.png");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
	
	int rotation = 0;
	int green = 0;
	int red = 0;

	while (!quit)
	{
		SDL_Delay(5000);
		SDL_PollEvent(&event);

		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
		}
		
		SDL_Rect dstrect = { 0, 0, 320, 320 };
		SDL_SetTextureColorMod( texture, red, green, 0 );
		SDL_RenderCopyEx(renderer, texture, NULL, &dstrect, rotation, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(renderer);

		if (!ping() && rotation < 90) 
		{
			rotation = rotation + 18;
		} 
		else if (!ping() && rotation >= 90)
		{
			rotation = 90;
			red = 255;
			green = 0;
			int duration = 1000;
		  double Hz = 440;

	    Beeper b;
	    b.beep(Hz, duration);
	    b.wait();
		}
		else 
		{
			rotation = 0;
			green = 255;
			red = 0;
		}
	}

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}