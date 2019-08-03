#include "Zombie.h"
#include "Human.h"

#include <ctime>
#include <gtx/rotate_vector.hpp>
#include <random>

Zombie::Zombie(float speed, glm::vec2 pos) {
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

	Human* closestHuman = getNearestHuman(humans);

	glm::vec2 distVec(1.0f, 10.f);

	if (closestHuman != nullptr) {
		glm::vec2 distVec = glm::normalize(closestHuman->getPosition() - _position);
		_position += distVec * _speed * deltaTime;
	}

	collideWithLevel(levelData);
}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans) 
{
	Human* closestHuman = nullptr;
	float smallestDistance = 99999.f;
	for (size_t i = 0; i < humans.size(); i++)
	{
		glm::vec2 distVec = humans[i]->getPosition() - _position;
		float distance = glm::length(distVec);
		
		if (distance < smallestDistance) {
			smallestDistance = distance;
			closestHuman = humans[i];
		}
	}
	return closestHuman;
}