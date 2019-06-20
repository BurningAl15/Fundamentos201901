#include <SDL\SDL.h>
#include <GL\glew.h>
#include "PapuEngine.h"
#include <iostream>
#include "SoundManager.h"
using namespace std;

namespace Papu {
	int init() {
	
		SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO);

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Error: " << Mix_GetError() << endl;
		}
		//SoundManager* manager = new SoundManager();
		//SoundManager* manager = new SoundManager("Sounds/PXNDX-Disculpa los Malos Pensamientos.mp3");

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		return 0;
	}
}

