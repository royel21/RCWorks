#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <string>
#include <fstream>
#include <PlutusEngine/SpriteBatch.h>

const int TILE_WIDTH = 64;

class Level
{
private:
	std::vector<std::string> _data;
	uint32_t _nHumans;
	PlutusEngine::SpriteBatch _spriteBath;

	glm::ivec2 _playerPos;
	std::vector<glm::ivec2> _zombiesPos;
	uint32_t _titleWidth;
	uint32_t _titleHeight;
	std::vector<glm::ivec2> _freePos;
public:
	Level(std::string name);
	~Level();

	void draw();
	const std::vector<std::string>& getData() const { return _data; }

	glm::vec2 getPlayerPos() const { return _playerPos; }

	std::vector<glm::ivec2> getZombiesPos() const { return _zombiesPos; }

	std::vector<glm::ivec2> getFreePos() const { return _freePos; }

	uint32_t getNumHumans() const { return _nHumans; }

	uint32_t getWidth() { return (uint32_t)_data[0].size(); }

	uint32_t getHeight() { return (uint32_t)_data.size(); }
};
#endif
