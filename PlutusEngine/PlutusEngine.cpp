// PlutusEngine.cpp : Defines the functions for the static library.
//

#include "PlutusEngine.h"
namespace PlutusEngine {
	
	int init() {

		//Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//Set up double buffering so we don't get any flickering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}

}