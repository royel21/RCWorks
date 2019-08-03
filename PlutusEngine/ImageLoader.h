#pragma once
#include "GLTexture.h"
#include <string>
namespace PlutusEngine {
	//Load images into GLTexture
	class ImageLoader
	{
	public:
		static GLTexture LoadPNG(std::string filePath);
	};
}
