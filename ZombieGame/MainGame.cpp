#include "MainGame.h"
#include "Level.h"
#include <ctime>
#include <random>
#include <assert.h>
#include <algorithm>

#include "vertexshaders.h"
#include "fragshaders.h"

const int MAX_PHYSICS_STEPS = 6;

const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.3f;
const float CAMERA_SCALE = 2.0f;
const float DESIRE_FPS = 60.0f;
const float MS_PER_SECOND = 1000.0f;
const float MAX_DELTATIME = 1.0f;
const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRE_FPS;

MainGame::MainGame() :
	_screenHeight(768),
	_screenWidth(1024),
	_maxFPS(30.0f),
	_fps(0.0f),
	_currentLevel(0),
	_nHumansKilled(0),
	_nZombiesKilled(0),
	_player(nullptr),
	_gameState(GameState::PLAY)
{
	_camera.init(_screenWidth, _screenHeight);
}
MainGame::~MainGame()
{
	for (auto &l : _levels) {
		delete l;
	}
	for (auto &h : _humans) {
		delete h;
	}
	for (auto &z : _zombies) {
		delete z;
	}
}
void MainGame::run() {
	//Initialize the game system
	initSystems();

	//Never ending loop to process the game logic
	gameLoop();

}

void MainGame::initSystems() {
	PlutusEngine::init();
	_window.createWin("Game Engine", _screenWidth, _screenHeight, 0);
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);

	initShaders();

	initLevel();

	_spriteBatch.init();

	_fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders() {
	_textureProgram.compileShaders(vertexShader, fragShader);
	_textureProgram.addAtribute("vertexPosition");
	_textureProgram.addAtribute("vertexColor");
	_textureProgram.addAtribute("vertexUV");
	_textureProgram.linkShaders();
}

void MainGame::initLevel()
{
	_levels.push_back(new Level("resources/levels/level1.txt"));
	_player = new Player(5.0f, _levels[_currentLevel]->getPlayerPos(), &_inputManager, &_camera, &_bullets);

	_humans.push_back(_player);
	auto freePos = _levels[_currentLevel]->getFreePos();
	std::mt19937 randomEngine((int)time(nullptr));
	std::uniform_int_distribution<int> randPos(0, (int)freePos.size() - 1);

	//add all humans
	for (uint32_t i = 0; i < _levels[_currentLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human());
		glm::vec2 hPos = glm::vec2(freePos[randPos(randomEngine)]);
		//std::cout << "X: " << hPos.x << " Y: " << hPos.y << std::endl;
		_humans.back()->init(HUMAN_SPEED, hPos);
	}
	//Add Zombies
	for (auto zPos : _levels[_currentLevel]->getZombiesPos())
	{
		_zombies.push_back(new Zombie(ZOMBIE_SPEED, zPos));
	}
	_player->addGun(new Gun("PieceMaker", _player->getPosition(), 5, 4, 30, 0, 20.0f, "piecemarker.png"));
	_player->addGun(new Gun("Magnum", _player->getPosition(), 9, 10, 20, .5f, 20.0f, "piecemarker.png"));

}

void MainGame::gameLoop() {


	_fpsLimiter.setMaxFPS(60);
	_camera.setScale(CAMERA_SCALE);
	uint32_t lastTick = SDL_GetTicks();

	while (_gameState != GameState::EXIT) {
		_fpsLimiter.begin();


		uint32_t newTick = SDL_GetTicks();
		float frameTime = (float)(newTick - lastTick);
		lastTick = newTick;

		float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

		_inputManager.update();

		//CheckWinCondition();

		processInput();

		int i = 0;
		while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
			float deltaTime = std::min(totalDeltaTime, MAX_DELTATIME);
			updateCharacters(deltaTime);
			updateBullets(deltaTime);
			totalDeltaTime -= deltaTime;
			i++;
		}

		//Update the camera relative to the player
		_camera.setPosition(_player->getPosition());

		_camera.update();

		drawGame();

		_fps = _fpsLimiter.end();
		static int frameCount = 0;
		frameCount++;
		if (frameCount == 100) {
			_window.setWindowTitle("FPS: " + std::to_string(_fps));
			frameCount = 0;
		}
	}
}

void MainGame::updateCharacters(float deltaTime)
{

	for (auto h: _humans)
	{
		h->update(_levels[_currentLevel]->getData(), _humans, _zombies, deltaTime);
	}

	//Update all zombies
	for (auto z : _zombies)
	{
		z->update(_levels[_currentLevel]->getData(), _humans, _zombies, deltaTime);
	}

	//update Zombie collisions

	for (uint32_t i = 0; i < _zombies.size(); i++)
	{
		//Collide with other zombies
		for (uint32_t j = i + 1; j < _zombies.size(); j++) {
			_zombies[i]->collideWithCharacter(_zombies[j]);
		}

		for (uint32_t j = 1; j < _humans.size(); j++) {
			if (_zombies[i]->collideWithCharacter(_humans[j])) {
				//Convert Human to zombie
				_zombies.push_back(new Zombie(ZOMBIE_SPEED, _humans[j]->getPosition()));
				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}
		}
		//Collide with player
		if (_zombies[i]->collideWithCharacter(_player)) {
			std::cout << "You Lose" << std::endl;
		}
	}

	//update humans collision
	for (int i = 0; i < _humans.size(); i++) {
		// Collide with other humans
		for (int j = i + 1; j < _humans.size(); j++) {
			_humans[i]->collideWithCharacter(_humans[j]);
		}
	}

}

void MainGame::updateBullets(float deltaTime) {

	//Update the bullets
	for (int i = (int)_bullets.size() - 1; i > -1; i--)
	{
		if (_bullets[i].update(_levels[_currentLevel]->getData(), deltaTime)) {
			_bullets.erase(_bullets.begin() + i);
		}
	}

	//Collide with characters
	for (int i = (int)_bullets.size() -1; i > -1; i--)
	{
		for (int j = (int)_zombies.size()-1; j > -1 ; j-- )
		{
			if (j < 0) break;
			if (_bullets[i].collideWithCharacter(_zombies[j])) {

				if (_zombies[j]->applyDamage(_bullets[i].getDamage())) {
					delete _zombies[j];
					_zombies.erase(_zombies.begin() + j);
					_nZombiesKilled++;
				}
				//Remove the bullet
				_bullets.erase(_bullets.begin() + i);
				i--;
				break;
			} 
		}

		if (i < 0) continue;

		for (int j = (int)_humans.size() -1; j > 0; j--)
		{
			if (_bullets[i].collideWithCharacter(_humans[j])) {

				if (_humans[j]->applyDamage(_bullets[i].getDamage())) {
					delete _humans[j];
					_humans.erase(_humans.begin() + j);
					_nHumansKilled++;
				}
				//Remove the bullet
				_bullets.erase(_bullets.begin() + i);
				break;
			}
		}
	}

}

void MainGame::CheckWinCondition()
{

	if (_zombies.empty()) {
		std::printf("You Won!, you killed %d Humans and killed %d Zombies, Humans left %d/%d \n", 
			_nHumansKilled , 
			_nZombiesKilled, 
			(int)_humans.size()-1, 
			(int)_levels[_currentLevel]->getNumHumans());
	}
}

void MainGame::processInput() {
	SDL_Event wEvent;

	while (SDL_PollEvent(&wEvent)) {
		switch (wEvent.type) {
		case SDL_QUIT: {
			_gameState = GameState::EXIT;
			break;
		}

		case SDL_KEYDOWN: {
			_inputManager.pressKey(wEvent.key.keysym.sym);

			break;
		}
		case SDL_KEYUP: {
			_inputManager.releaseKey(wEvent.key.keysym.sym);
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			_inputManager.pressKey(wEvent.button.button);
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			_inputManager.releaseKey(wEvent.button.button);
			break;
		}
		case SDL_MOUSEMOTION:
		{
			_inputManager.setMouseCoords((float)wEvent.motion.x, (float)wEvent.motion.y);
			break;
		}
		}
	}
}

void MainGame::drawGame() {
	//Set the base depth to 1.0f
	glClearDepth(1.0f);
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Activate the vertex program
	_textureProgram.use();
	//Tell the gpu that we want to use texture 0
	GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureUniform, 0);
	/***********************************/

	//Get the location of P and Set the camera matrix 
	GLuint pLocation = _textureProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	/***********************************/
	_levels[_currentLevel]->draw();

	_spriteBatch.begin();

	const glm::vec2 characDim(CharacRadius*2);

	//Draw the humans
	for (auto h : _humans)
	{
		if (_camera.isBoxInView(h->getPosition(), characDim)) {
			h->draw(_spriteBatch);
		}
	}

	//Draw the Zombies
	for (auto z : _zombies)
	{
		if (_camera.isBoxInView(z->getPosition(), characDim)) {
			z->draw(_spriteBatch);
		}
	}

	//Draw all the bullets
	for (auto b : _bullets)
	{
		if (_camera.isBoxInView(b.getPosition(), characDim)) {
			b.draw(_spriteBatch);
		}
	}

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	//Deactivate the vertex program
	_textureProgram.unuse();

	_window.swapBuffer();
}