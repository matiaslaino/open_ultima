#include "VerticalScrollingTileAnimation.h"

VerticalScrollingTileAnimation::VerticalScrollingTileAnimation(int tileWidth, int tileHeight)
	: _tileWidth(tileWidth), _tileHeight(tileHeight)
{
	_frame.x = 0;
	_frame.y = tileHeight;
	_frame.w = tileWidth;
	_frame.h = tileHeight;

	_scroll = _frame.y;
}

void VerticalScrollingTileAnimation::animate(float timeElapsedSeconds)
{
	_scroll -= (_tileHeight / 2) * timeElapsedSeconds;
	if (_scroll <= 0) _scroll = _tileHeight;
	_frame.y = (int)(_scroll);

}

SDL_Rect VerticalScrollingTileAnimation::getFrame()
{
	return _frame;
}