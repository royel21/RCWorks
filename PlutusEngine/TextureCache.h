#pragma once
#include <map>
#include <string>
#include "GLTexture.h"

namespace PlutusEngine {

	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string texurePath);

	private:
		std::map<std::string, GLTexture> _textureMap;

	};

}