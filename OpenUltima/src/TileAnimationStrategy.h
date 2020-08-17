#pragma once
#include <SDL_rect.h>
class TileAnimationStrategy {
public:
	virtual void animate(float timeElapsedSeconds) = 0;
	virtual SDL_Rect getFrame() = 0;
};