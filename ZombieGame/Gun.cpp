#include "Gun.h"

#include <gtx/rotate_vector.hpp>
#include <ctime>
#include <random>


/*Player* player,
int width,
int height,
int fireRate,
int bulletsPerShot,
int bulletDamage,
float spread,
float bulletSpeed,
std::string imgName*/
//Set up player Guns
Gun::Gun(
	std::string gunName,
	const glm::vec2 position,
	int fireRate,
	int bulletsPerShot,
	int bulletDamage,
	float spread,
	float bulletSpeed,
	std::string imgName) :
	_gunName(gunName),
	_width(0), _height(0)

{
	_position = glm::vec2(position);
	_fireRate = fireRate;
	_bulletForShot = bulletsPerShot;
	_spread = spread;
	_bulletSpeed = bulletSpeed;
	_frameCount = 0;
	_bulletDamage = bulletDamage;
	_texture = PlutusEngine::ResourceManager::getTexture("resources/textures/" + imgName);
}

Gun::~Gun()
{
}

void Gun::draw(PlutusEngine::SpriteBatch& spbatch)
{
	PlutusEngine::ColorRGBA8 color(255, 255, 255, 255);


	glm::vec4 destRect = glm::vec4(_position, _width, _height);
	glm::vec4 uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	spbatch.draw(destRect, uvRect, _texture.id, 0.0f, color);
}

void Gun::update(
	bool isMDown,
	const glm::vec2& position,
	const glm::vec2& direction,
	std::vector<Bullet>& bullets, float deltaTime)
{
	_frameCount += 1.0f * deltaTime;

	if (_frameCount >= _fireRate && isMDown) {
		fire(position, direction, bullets);
		_frameCount = 0;
	}
	else {
		_frameCount++;
	}
}

void Gun::fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets)
{
	static std::mt19937 randomEngine((uint32_t)time(nullptr));
	std::uniform_real_distribution<float> randSpread(-_spread, _spread);
	for (int i = 0; i < _bulletForShot; i++)
	{
		bullets.emplace_back(
			position,
			glm::rotate(direction, randSpread(randomEngine)),
			_bulletDamage,
			_bulletSpeed);
		
	}
}
