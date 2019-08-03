#include "Timing.h"
#include <SDL.h>

namespace PlutusEngine {
	FpsLimiter::FpsLimiter() : _maxFPS(60), _startTick(0)
	{
	}
	void FpsLimiter::init(float maxFPS)
	{
		setMaxFPS(maxFPS);
	}
	void FpsLimiter::setMaxFPS(float maxFPS)
	{
		_maxFPS = maxFPS;
	}
	void FpsLimiter::begin()
	{
		_startTick = SDL_GetTicks();
	}
	float FpsLimiter::end()
	{
		calculateFPS();

		float frameTicks = (float)(SDL_GetTicks() - _startTick);
		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay((Uint32)(1000.0f / _maxFPS - frameTicks));
		}

		return _fps;
	}

	void FpsLimiter::calculateFPS()
	{
		static const int NUM_SAMPLES = 10;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		static float prevTicks = (float)SDL_GetTicks();

		//_fps = 1000.0 / (SDL_GetTicks() - prevTicks);

		float currentTicks = (float)SDL_GetTicks();
		_frameTime = currentTicks - prevTicks;

		frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

		prevTicks = (float)SDL_GetTicks();

		int count;

		currentFrame++;

		if (currentFrame < NUM_SAMPLES) {
			count = currentFrame;
		}
		else {
			count = NUM_SAMPLES;
		}

		float frameTimeAverage = 0;

		for (int i = 0; i < count; i++) {
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= count;
		if (frameTimeAverage > 0) {
			_fps = 1000.0f / frameTimeAverage;
		}
		else {
			_fps = 60.0f;
		}
	}
}