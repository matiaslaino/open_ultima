#include "HorizontalSwapTileAnimation.h"

HorizontalSwapTileAnimation::HorizontalSwapTileAnimation(int tileWidth, int tileHeight)
	: _tileWidth(tileWidth), _tileHeight(tileHeight)
{
	for (int i = 0; i < FRAMES_COUNT; i++) {
		SDL_Rect frame = { i * tileWidth, 0, tileWidth, tileHeight };
		_clips.push_back(frame);
	}
}

void HorizontalSwapTileAnimation::animate(float timeElapsedSeconds)
{
	_animationCounter += timeElapsedSeconds;

	if (_animationCounter >= 3) {
		_animationCounter = 0;
		_currentFrame = (_currentFrame + 1) % FRAMES_COUNT;
	}
}

SDL_Rect HorizontalSwapTileAnimation::getFrame()
{
	return _clips[_currentFrame];
}
