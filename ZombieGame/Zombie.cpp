#include "Zombie.h"
#include "Human.h"

#include <ctime>
#include <gtx/rotate_vector.hpp>
#include <random>

Zombie::Zombie(float speed, glm::vec2 pos) : _direction(0), _frame(0) {
	_speed = speed;
	_position = pos;
	_health = 200;
	_texture = PlutusEngine::ResourceManager::getTexture("resources/textures/zombie.png");
}

void Zombie::update(
	const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies, float deltaTime
) {


	Human* closestHuman = (Human*)getNearestCharacter((std::vector<Character*>&)humans, 99999.0f);

	glm::vec2 distVec(1.0f, 10.f);
	//Follow the humans
	if (closestHuman != nullptr) {
		glm::vec2 distVec = glm::normalize(closestHuman->getPosition() - _position);
		_position += distVec * _speed * deltaTime;
	}

	collideWithLevel(levelData);
}