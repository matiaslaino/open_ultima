#pragma once
#include "TileAnimationStrategy.h"
#include <vector>

using namespace std;

class HorizontalSwapTileAnimation: public TileAnimationStrategy
{
public:
	HorizontalSwapTileAnimation(int tileWidth, int tileHeight);
	virtual void animate(float timeElapsedSeconds) override;
	virtual SDL_Rect getFrame();
private:
	static constexpr int FRAMES_COUNT = 2;
	static constexpr int PERIOD = 2;

	int _tileWidth;
	int _tileHeight;
	vector<SDL_Rect> _clips;
	int _currentFrame = 0;
	float _animationCounter = 0;
};

