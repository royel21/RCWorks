#include "Bullet.h"
#include "Human.h"
#include "Zombie.h"
#include "Character.h"
#include "Level.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, int damage, float speed) :
	_position(position),
	_direction(direction),
	_damage(damage),
	_speed(speed)
{
	_texture = PlutusEngine::ResourceManager::getTexture("resources/textures/circle.png");
}

Bullet::~Bullet()
{

}

bool Bullet::update(const std::vector<std::string>& levelData, float deltaTime)
{
	_position += _direction * _speed * deltaTime;
	return collideWithWorld(levelData);
}

void Bullet::draw(PlutusEngine::SpriteBatch& spriteBatch)
{
	PlutusEngine::ColorRGBA8 color(32, 32, 32, 255);

	glm::vec4 destRect(
		_position.x + BULLET_RADIUS,
		_position.y + BULLET_RADIUS,
		BULLET_RADIUS,
		BULLET_RADIUS
	);

	glm::vec4 uvRect(1.0f, 1.0f, 1.0f, 1.0f);

	spriteBatch.draw(destRect, uvRect, _texture.id, 0.0f, color);

}

bool Bullet::collideWithCharacter(Character* chara)
{
	const float MIN_DISTANCE = CharacRadius + BULLET_RADIUS;

	glm::vec2 centerPosA = _position;
	glm::vec2 centerPosB = chara->getPosition() + glm::vec2(CharacRadius);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;
	if (collisionDepth > 0) {
		
		return true;
	}

	return false;
}

bool Bullet::collideWithWorld(const std::vector<std::string>& levelData)
{
	int nX = floor(_position.x / (float)TILE_WIDTH);
	int nY = floor(_position.y / (float)TILE_WIDTH);
	if (nY < 0 || nX < 0 || nY > (int)levelData.size()-1 || nX > (int)levelData[0].size()-1) return true;

	return (levelData[nY][nX] != '.');
}

