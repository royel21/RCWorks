#include "Player.h"
#include <iostream>
#include "Gun.h"

Player::Player(
	float speed, 
	glm::vec2 pos, 
	PlutusEngine::InputManager* input, 
	PlutusEngine::Camera2D* camera,
	std::vector<Bullet>* bullets
)
{
	_speed = speed;
	_position = pos;
	_lastPosition = pos;
	_width = 60;
	_height = 60;
	_input = input;
	_currentGun = -1;
	_camera = camera;
	_bullets = bullets;
	_health = 150;
	_texture = PlutusEngine::ResourceManager::getTexture("resources/textures/player.png");
}

Player::~Player()
{
	for (auto &g : _guns)
	{
		delete g;
	}
	_guns.clear();
}

void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies, float deltaTime)
{
	if (_input->isKeyDown(SDLK_UP)) {
		_position.y += _speed * deltaTime;
	}
	else if (_input->isKeyDown(SDLK_DOWN)) {
		_position.y -= _speed * deltaTime;
	}

	if (_input->isKeyDown(SDLK_LEFT)) {
		_position.x -= _speed * deltaTime;
	}
	else if (_input->isKeyDown(SDLK_RIGHT)) {
		_position.x += _speed * deltaTime;
	}

	if (_input->isKeyDown(SDLK_1)) {
		_currentGun = 0;
	}

	if (_input->isKeyDown(SDLK_2)) {
		_currentGun = 1;
	}

	if (_currentGun != -1) {
		glm::vec2 mCoords = _input->getMouseCoords();
		mCoords = _camera->convertScreenToWold(mCoords);
		glm::vec2 centerPos = _position + glm::vec2(CharacRadius);

		glm::vec2 direction = glm::normalize(mCoords - centerPos);

		_guns[_currentGun]->update(
			_input->isKeyDown(SDL_BUTTON_LEFT),
			_position, 
			direction, 
			*_bullets,
			deltaTime);
	}

	collideWithLevel(levelData); 
}

void Player::addGun(Gun* gun)
{
	_guns.push_back(gun);
	if (_currentGun) {
		_currentGun = 0;
	}
}


