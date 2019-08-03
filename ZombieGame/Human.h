#pragma once
#include "Character.h"

class Human : public Character
{
private:
	glm::vec2 _direction;
	int _frame;
public:
	Human();
	void init(float speed, glm::vec2 pos);

	virtual ~Human();

	virtual void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies, float deltaTime);
private:
	Zombie* getNearestZombie(std::vector<Zombie*>& zombie);
};

