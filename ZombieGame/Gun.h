#pragma once
#include <PlutusEngine/all.h>
#include <string>
#include <vector>
#include <glm.hpp>

#include "PLayer.h"
#include "Bullet.h"

class Gun
{
private:
	std::string _gunName;
	PlutusEngine::GLTexture _texture;
	glm::vec2 _position;

	int _width, _height;
	int _fireRate;
	float _spread; // Accuracy
	float _bulletSpeed;
	int _bulletDamage;
	int _bulletForShot; // How many bullets are fire at a time
	float _frameCount;

public:
	Gun(
		std::string gunName,
		const glm::vec2 position,
		int fireRate,
		int bulletsPerShot,
		int bulletDamage,
		float spread,
		float bulletSpeed,
		std::string imgName
	);
	~Gun();

	void draw(PlutusEngine::SpriteBatch& spbatch);

	void update(
		bool isMDown,
		const glm::vec2& position,
		const glm::vec2& direction,
		std::vector<Bullet>& bullets,
		float deltaTime
	);

private:
	void fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets);
};

