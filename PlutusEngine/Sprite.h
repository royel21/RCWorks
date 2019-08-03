#pragma once

#include <GL/glew.h>
#include <string>

#include "GLTexture.h"
#include "ResourceManager.h"

namespace PlutusEngine {
	class Sprite
	{
	private:
		float _width;
		float _height;
		float _x;
		float _y;
		GLuint _vBuffId;
		GLTexture _texture;

	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, std::string texturePath);
		void draw();
	};

}