#include "TextureCache.h"
#include "ImageLoader.h" 

#include <iostream>

namespace PlutusEngine {
	TextureCache::TextureCache()
	{
	}
	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		//lookup the texture and see if its in the map
		auto mit = _textureMap.find(texturePath);

		//check if the texture exist if not load a new one
		if (mit == _textureMap.end()) {
			//Load the texture
			GLTexture newTexture = ImageLoader::LoadPNG(texturePath);

			//Insert it into the map
			_textureMap.insert(make_pair(texturePath, newTexture));
			return newTexture;
		}
		return mit->second;
	}
}