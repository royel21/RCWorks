#include "Level.h"
#include <PlutusEngine/Errors.h>
#include <PlutusEngine/ResourceManager.h>

#include <algorithm>

#define log(x) std::cout << x << std::endl

Level::Level(std::string fileName) : _titleWidth(64), _titleHeight(64)
{
	std::ifstream file;
	file.open(fileName);
	if (file.fail()) {
		PlutusEngine::fatalError("Fail to open level -> " + fileName);
	}
	std::string tmp;

	file >> tmp >> _nHumans;

	std::getline(file, tmp);

	while (std::getline(file, tmp)) {
		_data.push_back(tmp);
	}

	_spriteBath.init();
	_spriteBath.begin();
	std::reverse(_data.begin(), _data.end());

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	for (size_t y = 0; y < _data.size(); y++)
	{
		for (size_t x = 0; x < _data[y].size(); x++)
		{
			char title = _data[y][x];
			glm::vec4 destRect(x * _titleWidth, y * _titleHeight, _titleWidth, _titleHeight);
			PlutusEngine::ColorRGBA8 color;
			color.r = 255;
			color.g = 255;
			color.b = 255;
			color.a = 255;

			switch (title)
			{
			case 'B':
			case 'R': {

				_spriteBath.draw(destRect, uvRect,
					PlutusEngine::ResourceManager::getTexture("resources/textures/red_bricks.png").id,
					0.0f, color);
				break;
			}
			case 'G': {
				_spriteBath.draw(destRect, uvRect,
					PlutusEngine::ResourceManager::getTexture("resources/textures/glass.png").id,
					0.0f, color);
				break;
			}
			case 'L': {
				_spriteBath.draw(destRect, uvRect,
					PlutusEngine::ResourceManager::getTexture("resources/textures/light_bricks.png").id,
					0.0f, color);
				break;
			}
			case '@': {
				_data[y][x] = '.';
				_playerPos = glm::vec2(x * _titleWidth, y * _titleHeight);
				break;
			}
			case 'Z': {
				_data[y][x] = '.';
				_zombiesPos.emplace_back(x * _titleWidth, y * _titleHeight);
				break;
			}
			case '.': {
				_freePos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
				break;
			}
			default:
				std::printf("Unexpected Symbol %c at x:%zu y:%zu", title, x, y);
				break;
			}
		}
	}
	_spriteBath.end();
}

Level::~Level()
{
}

void Level::draw()
{
	_spriteBath.renderBatch();
}
