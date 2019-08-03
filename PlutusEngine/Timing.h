#pragma once

namespace PlutusEngine {
	class FpsLimiter {
	public:
		FpsLimiter();
		void init(float maxFPS);
		
		void setMaxFPS(float maxFPS);

		void begin();
		//return the fps
		float end();

	private:
		float _maxFPS;
		unsigned int _startTick;

		float _fps;
		float _frameTime;

		void calculateFPS();
	};

}