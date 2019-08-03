#include "Window.h"
#include "Errors.h"

namespace PlutusEngine {

	Window::Window() :
		_sdl_window(nullptr),
		_glContext(nullptr),
		_screenWidth(640),
		_screenHeight(640)
	{
		
	}

	Window::~Window()
	{
		SDL_GL_DeleteContext(_glContext);
	}

	int Window::createWin(std::string wName, int width, int height, GLuint currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;
		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}

		if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		if (currentFlags & BORDELESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		_screenWidth = width;
		_screenHeight = height;
		_sdl_window = SDL_CreateWindow(wName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, flags);

		//quit if error creating window
		if (_sdl_window == nullptr) {
			PlutusEngine::fatalError("SDL Window could not be created");
		}
		//Create a gl context
		_glContext = SDL_GL_CreateContext(_sdl_window);

		//Set up glew and check for error
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			PlutusEngine::fatalError("Could not initialize glew!");
		}
		//Print the OpenGL Version
		std::printf("*** OpenGL Version %s ***\n", glGetString(GL_VERSION));

		//Set backgound color
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		//Set VSYNC
		SDL_GL_SetSwapInterval(0);
		
		//Enable alpha blend
		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer()
	{
		//Swap our buffer and draw everything to the screen
		SDL_GL_SwapWindow(_sdl_window);
	}

	void Window::setWindowTitle(std::string title)
	{
		SDL_SetWindowTitle(_sdl_window, title.c_str());
	}
}