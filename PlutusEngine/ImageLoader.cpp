#include "ImageLoader.h"
#include "stb_image.h"
#include "IOManager.h"
#include "Errors.h"

namespace PlutusEngine {
	GLTexture ImageLoader::LoadPNG(std::string filePath)
	{
		GLTexture texture = {};

		std::vector<GLubyte> in;
		uint8_t *out;

		int width, height, BPP;

		if (!IOManager::readFileToBuffer(filePath, in)) {
			fatalError("Failed to load PNG to buffer!");
		}

		out = stbi_load(filePath.c_str(), &width, &height, &BPP, 4);
		glGenTextures(1, &(texture.id));
		//link the image to a texture in the gpu texture array
		glBindTexture(GL_TEXTURE_2D, texture.id);
		//flag to render the image
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//Load the image to the memory of the gpu
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, out);
		
		//See https://en.wikipedia.org/wiki/Mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
		//unlink the image to a texture in the gpu texture array
		glBindTexture(GL_TEXTURE_2D, 0);
		texture.width = width;
		texture.height = height;
		if (out) {
			stbi_image_free(out);
		}
		return texture;
	}
}