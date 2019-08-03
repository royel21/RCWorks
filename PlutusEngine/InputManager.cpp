#include "InputManager.h"
namespace PlutusEngine {
	InputManager::InputManager() : _mouseCoords(0, 0), _keyMap(0)
	{
	}

	InputManager::~InputManager()
	{
	}

	void InputManager::update()
	{
		//Loop through keymap and copy it to prevKeyMap.
		for (auto& key : _keyMap) {
			_prevKeyMap[key.first] = key.second;
		}
	}

	void InputManager::pressKey(unsigned int keyId)
	{
		_keyMap[keyId] = true;
	}

	void InputManager::releaseKey(unsigned int keyId)
	{
		_keyMap[keyId] = false;
	}

	void InputManager::setMouseCoords(float x, float y)
	{
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}

	bool InputManager::isKeyDown(unsigned int keyId)
	{
		return _keyMap[keyId] ? true : false;
	}

	bool InputManager::isKeyPressed(unsigned int keyId)
	{
		//return true if key was not down last frame
		return isKeyDown(keyId) && !wasKeyDown(keyId);
	}

	bool InputManager::wasKeyDown(unsigned int keyId)
	{
		return _prevKeyMap[keyId] ? true : false;
		return false;
	}
}