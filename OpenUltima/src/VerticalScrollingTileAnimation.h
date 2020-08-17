#pragma once
#include "TileAnimationStrategy.h"
#include <vector>

using namespace std;

class VerticalScrollingTileAnimation :
    public TileAnimationStrategy
{
public:
	VerticalScrollingTileAnimation(int tileWidth, int tileHeight);
	virtual void animate(float timeElapsedSeconds) override;
	virtual SDL_Rect getFrame();
private:
	static constexpr float PERIOD = 0.5;

	int _tileWidth;
	int _tileHeight;
	SDL_Rect _frame;
	float _scroll = 0;
};

