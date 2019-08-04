#include "Camera2D.h"
#include <iostream>

namespace PlutusEngine {
	Camera2D::Camera2D() :
		_screenWidth(500),
		_screenHeight(500),
		_needsMatrixUpdate(true),
		_scale(1.0f),
		_position(0.0f, 0.0f),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f)
	{

	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int screenWidth, int screenHeight)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		//this is for convert the opengl espace -1.0 - 1.0 to 0 - screenW and height
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	void Camera2D::update()
	{
		if (_needsMatrixUpdate) {

			//camera translation
			glm::vec3 translate(-_position.x + _screenWidth/2, -_position.y + _screenHeight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			//Camera Scale
			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

			_needsMatrixUpdate = false;
		}
	}
	//Convert screen coordination to opengl coordination and return it
	glm::vec2 Camera2D::convertScreenToWold(glm::vec2 screenCoords)
	{
		//inver Y direction;
		screenCoords.y = _screenHeight - screenCoords.y;

		//Make that 0 is the center
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);

		//Scale the coordinates
		screenCoords /= _scale;

		//Translate with the camera position
		screenCoords += _position;

		return screenCoords;
	}

	bool Camera2D::isBoxInView(const glm::vec2 position, const glm::vec2 dim)
	{
		glm::vec2 scaleDim = glm::vec2(_screenWidth ,_screenHeight) / _scale;

		const float MIN_DISTANCE_X = dim.x / 2.0f + scaleDim.x / 2.0f;
		const float MIN_DISTANCE_Y = dim.y / 2.0f + scaleDim.y / 2.0f;

		glm::vec2 centerPos = position + dim / 2.0f;

		glm::vec2 distVec = centerPos - _position;

		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

		if (xDepth > 0 && yDepth > 0)
		{
			return true;
		}
		
		return false;
	}
}