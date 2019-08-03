#define SDL_MAIN_HANDLED
#include "MainGame.h"

int main(int argc, char** argv) {
	MainGame mainGame;

	mainGame.run();
	return 0;
}