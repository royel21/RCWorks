#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
namespace PlutusEngine {
	class Camera2D
	{
	private:
		int _screenWidth;
		int _screenHeight;
		bool _needsMatrixUpdate;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;

	public:
		Camera2D();
		~Camera2D();
		void init(int screenWidth, int screenHeight);

		void update();
		glm::vec2 convertScreenToWold(glm::vec2 screenCoords);
		//Setters
		void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
		void setScale(float newScale) { _scale = 1/newScale; _needsMatrixUpdate = true; }
		
		//Getters
		glm::vec2 getPosition() { return _position; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }
		float getScale() { return _scale; }

		bool isBoxInView(const glm::vec2 position, const glm::vec2 dim);

	};
}
