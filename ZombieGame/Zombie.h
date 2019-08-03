#pragma once
#include "Character.h"

class Zombie : public Character
{
private:
	Human* getNearestHuman(std::vector<Human*>& humans);
	glm::vec2 _direction;
	int _frame;

public:
	Zombie(float speed, glm::vec2 pos);
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies, float deltaTime);
};

