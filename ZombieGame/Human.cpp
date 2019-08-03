#include <gtx/rotate_vector.hpp>
#include <ctime>
#include <random>

#include "Human.h"
#include "Zombie.h"

Human::Human() : _frame(0), _direction(0)
{
	_health = 60;
}

void Human::init(float speed, glm::vec2 pos)
{
	_speed = speed;
	_position = pos;
	//Asign the character sprite
	_texture = PlutusEngine::ResourceManager::getTexture("resources/textures/human.png");

	//Create a random direction
	static std::mt19937 randomEngine((uint32_t)time(nullptr));

	static std::uniform_real_distribution<float> randDir(0, 50.0f);

	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	//make sure direction is not zero
	if (_direction.length() == 0)
		_direction = glm::vec2(1.0f, 0.0f);

	_direction = glm::normalize(_direction);
}

Human::~Human()
{
}

void Human::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies, float deltaTime)
{
	static std::mt19937 randomEngine((uint32_t)time(nullptr));
	static std::uniform_real_distribution<float> randRotate(-40.0f, 40.0f);
	
	Zombie* closestZombies = getNearestZombie(zombies);

	if (closestZombies != nullptr) {
		glm::vec2 distVec = glm::normalize(closestZombies->getPosition() - _position);
		_position -= _direction + distVec * _speed * deltaTime;
	}
	else
	{
		_position += _direction * _speed * deltaTime;
	}

	if (collideWithLevel(levelData))
	{
		_direction = glm::rotate(_direction, randRotate(randomEngine));
	}
}


Zombie* Human::getNearestZombie(std::vector<Zombie*>& zombie)
{
	Zombie* closestZombie = nullptr;
	float smallestDistance = 9999.f;
	for (size_t i = 0; i < zombie.size(); i++)
	{
		glm::vec2 distVec = zombie[i]->getPosition() - _position;
		float distance = glm::length(distVec);

		if (distance < smallestDistance) {
			smallestDistance = distance;
			closestZombie = zombie[i];
		}
	}

	return closestZombie;
}