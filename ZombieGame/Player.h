#pragma once
#include <glm.hpp>
#include <SDL.h>
#include <vector>
#include <PlutusEngine/Camera2D.h>
#include "Bullet.h"
#include "Human.h"

class Gun;

class Player : public Human
{
private:
	PlutusEngine::InputManager* _input;
	PlutusEngine::Camera2D* _camera;
	std::vector<Gun*> _guns;
	int _currentGun;
	std::vector<Bullet>* _bullets;
public:
	Player(
		float speed,
		glm::vec2 pos,
		PlutusEngine::InputManager* input,
		PlutusEngine::Camera2D* camera,
		std::vector<Bullet>* bullets);
	~Player();

	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies, float deltaTime);

	void addGun(Gun* gun);
};

