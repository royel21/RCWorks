#pragma once

#include <SDL.h>
#include <gl/glew.h>
#include <string>
namespace PlutusEngine {
	
	enum WindowFlags { INVISIBLE = 0x01, FULLSCREEN = 0x02, BORDELESS = 0x04 };

	class Window
	{
	public:
		Window();
		~Window();

		int createWin(std::string wName, int width, int height, GLuint currentFlags);

		void swapBuffer();

		int getWinHeight() { return _screenHeight; };
		int getWinWidth() { return _screenWidth; };
		void setWindowTitle(std::string title);

	private:
		SDL_Window* _sdl_window;
		SDL_GLContext _glContext;
		int _screenWidth;
		int _screenHeight;
	};
}