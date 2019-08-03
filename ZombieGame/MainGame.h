#pragma once
#include <SDL.h>
#include <GL/glew.h>

#include <PlutusEngine/all.h>

#include "Level.h"
#include "Human.h"
#include "Player.h"
#include "Zombie.h"
#include "Gun.h"
#include "Bullet.h"

enum class GameState {
	PLAY,
	EXIT
};

class MainGame
{
private:
	int _screenHeight;
	int _screenWidth;
	float _maxFPS;
	float _fps;
	uint32_t _currentLevel;
	uint32_t _nHumansKilled;
	uint32_t _nZombiesKilled;

	//Player pointer
	Player* _player;

	//Array of level pointer
	std::vector<Level*> _levels;

	//Array of humans pointer
	std::vector <Human*> _humans;

	//Array of zombies pointer
	std::vector<Zombie*> _zombies;

	std::vector<Bullet> _bullets;

	PlutusEngine::Window _window;

	PlutusEngine::GLSLProgram _textureProgram;

	PlutusEngine::InputManager _inputManager;

	PlutusEngine::Camera2D _camera;

	PlutusEngine::FpsLimiter _fpsLimiter;

	PlutusEngine::SpriteBatch _spriteBatch;

	GameState _gameState;

public:
	MainGame();
	~MainGame();

	void run();

private:
	//Initialize Core System
	void initSystems();

	//Initialize the shader program
	void initShaders();

	//Initialize the level
	void initLevel();

	//Main game loop
	void gameLoop();

	//Update the character and its positions
	void updateCharacters(float deltaTime);

	//Process the inputs
	void processInput();

	//Draw all the graphics
	void drawGame();

	void updateBullets(float deltaTime);

	void CheckWinCondition();
};


