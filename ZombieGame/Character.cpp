#include "Character.h"
#include <iostream>
#include <algorithm>
#include <PlutusEngine/vertex.h>

Character::Character() :
	_health(0),
	_speed(0),
	_width(60.0f),
	_height(60.0f),
	_position(0),
	_texture()
{
	_uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	_color = PlutusEngine::ColorRGBA8(255, 255, 255, 255);
}

Character::~Character()
{
}

bool Character::collideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePosition;

	// Check the for corners
	// First corner
	checkTilePosition(collideTilePosition, levelData, _position.x, _position.y);
	// First corner
	checkTilePosition(collideTilePosition, levelData, _position.x + CHARAC_WIDTH, _position.y);
	// First corner
	checkTilePosition(collideTilePosition, levelData, _position.x, _position.y + CHARAC_WIDTH);
	// First corner
	checkTilePosition(collideTilePosition, levelData, _position.x + CHARAC_WIDTH, _position.y + CHARAC_WIDTH);

	for (size_t i = 0; i < collideTilePosition.size(); i++)
	{
		collideWithTile(collideTilePosition[i]);
	}
	return collideTilePosition.size() ? true : false;
}

bool Character::collideWithCharacter(Character* character)
{
	const float MIN_DISTANCE = CharacRadius * 2.0f;

	glm::vec2 centerPosA = _position + glm::vec2(CharacRadius);
	glm::vec2 centerPosB = character->getPosition() + glm::vec2(CharacRadius);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;
	if (collisionDepth > 0) {
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;

		_position += collisionDepthVec / 2.0f;
		character->_position -= collisionDepthVec / 2.0f;

		return true;
	}

	return false;
}

//AABB Collision
void Character::collideWithTile(glm::vec2 tileP)
{
	const float TitleRadius = TILE_WIDTH / 2.0f;

	const float MIN_DISTANCE = CharacRadius + TitleRadius;

	glm::vec2 centerPlayerPos = _position + glm::vec2(CharacRadius);
	glm::vec2 distVec = centerPlayerPos - tileP;

	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);

	if (xDepth > 0 && yDepth > 0)
	{
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f))
		{
			if (distVec.x < 0) {
				_position.x -= xDepth;
			}
			else {
				_position.x += xDepth;
			}
		}
		else
		{
			if (distVec.y < 0) {
				_position.y -= yDepth;
			}
			else {
				_position.y += yDepth;
			}
		}
	}
}

void Character::checkTilePosition(std::vector<glm::vec2>& collideTilePosition,
	const std::vector<std::string>& levelData,
	float x, float y)
{
	
	int nX = floor(x / (float)TILE_WIDTH);
	int nY = floor(y / (float)TILE_WIDTH);
	if (nY < 0 || nX < 0) return;
	if (levelData[nY][nX] != '.')
	{
		glm::vec2 cornerPos = glm::vec2(nX, nY);
		collideTilePosition.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2(TILE_WIDTH / 2));
	}
}
void Character::draw(PlutusEngine::SpriteBatch& _spriteBatch)
{
	glm::vec4 destRect = glm::vec4(_position, _width, _height);

	_spriteBatch.draw(destRect, _uvRect, _texture.id, 0.0f, _color);
}

bool Character::applyDamage(int damage) {
	_health -= damage;
	return _health <= 1;
}