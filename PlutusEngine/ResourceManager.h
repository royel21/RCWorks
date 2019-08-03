#pragma once
#include <string>

#include "TextureCache.h"
namespace PlutusEngine {
	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);

	private:
		static TextureCache _textureCache;

	};

}