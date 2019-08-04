#pragma once
#include <PlutusEngine/all.h>

class Human;
class Zombie;
class Character;

const int BULLET_RADIUS = 10;

class Bullet {
private:
	glm::vec2 _position;
	glm::vec2 _direction;
	int _damage;
	float _speed;
	PlutusEngine::GLTexture _texture;


public:
	Bullet(const glm::vec2 position, const glm::vec2 direction, int damage, float speed);
	~Bullet();

	bool update(const std::vector<std::string>& levelData, float deltaTime);

	void draw(PlutusEngine::SpriteBatch& spriteBatch);

	bool collideWithCharacter(Character* chara);

	int getDamage() const { return _damage; }

	glm::vec2 getPosition() const { return _position; }

private:
	bool collideWithWorld(const std::vector<std::string>& levelData);
};

