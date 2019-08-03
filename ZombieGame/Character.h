#pragma once

#include <PlutusEngine/all.h>
#include <glm.hpp>
#include <string>
#include "Level.h"

class Zombie;
class Human;

const float CHARAC_WIDTH = 60.0f;
const float CharacRadius = 30.0f;

class Character
{
protected:
	int _health;
	float _speed;
	float _width, _height;
	glm::vec2 _position;
	glm::vec4 _uvRect;
	PlutusEngine::ColorRGBA8 _color;
	PlutusEngine::GLTexture _texture;

public:
	Character();
	virtual ~Character();

	virtual void update(
		const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies, float deltaTime
	) = 0;

	bool collideWithLevel(const std::vector<std::string>& levelData);

	bool collideWithCharacter(Character* character);

	void draw(PlutusEngine::SpriteBatch& _spriteBatch);

	glm::vec2 getPosition() const { return _position; }

	bool applyDamage(int damage);

protected:
	void checkTilePosition(std::vector<glm::vec2>& collideTilePosition,
		const std::vector<std::string>& levelData,
		float x, float y);

	void collideWithTile(glm::vec2 tileP);
};