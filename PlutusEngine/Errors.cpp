#include "Errors.h"
#include <cstdlib>
namespace PlutusEngine {
	void fatalError(std::string errorString) {
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit" << std::endl;
		std::cin.get();
		SDL_Quit();
		exit(1);
	}
}
