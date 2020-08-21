#include "TileAnimation.h"

void TileAnimation::update(float elapsed, AnimationType animationType, SDL_Rect box)
{
	switch (animationType) {
	case AnimationType::NOP:
		break;
	case AnimationType::SCROLLING:
		_scroll += (box.h / 2) * elapsed;
		if (_scroll >= box.h) _scroll = 0;
		break;
	case AnimationType::SWAP:
		_swapCounter += elapsed;

		if (_swapCounter >= 3) {
			_swapCounter = 0;
			_swapped = !_swapped;
		}
		break;
	}
}

vector<TileAnimation::RenderQuad> TileAnimation::getRenderQuads(SDL_Renderer* renderer, AnimationType animationType, SDL_Rect spriteBox, SDL_Rect textureSpriteSource, int swapOffset)
{
	vector<TileAnimation::RenderQuad> result;

	switch (animationType) {
	case AnimationType::NOP:
	{
		SDL_Rect renderQuadNop = { spriteBox.x, spriteBox.y, spriteBox.w, spriteBox.h };
		result.push_back(TileAnimation::RenderQuad(textureSpriteSource, renderQuadNop));
	}
	break;
	case AnimationType::SCROLLING:
	{
		// TODO check copy of rect
		int scrollOffset = (int)_scroll;

		SDL_Rect upperPortionSource = { textureSpriteSource.x, 0, 16, scrollOffset };
		SDL_Rect lowerPortionSource = { textureSpriteSource.x, scrollOffset, 16, spriteBox.h - scrollOffset };
		SDL_Rect upperRenderQuad = { spriteBox.x, spriteBox.y, spriteBox.w, spriteBox.h - scrollOffset };
		SDL_Rect lowerRenderQuad = { spriteBox.x, spriteBox.y + spriteBox.h - scrollOffset, spriteBox.w, scrollOffset };

		result.push_back(TileAnimation::RenderQuad(lowerPortionSource, upperRenderQuad));
		result.push_back(TileAnimation::RenderQuad(upperPortionSource, lowerRenderQuad));
	}
	break;
	case AnimationType::SWAP:
	{
		int textureOffset = _swapped ? swapOffset : textureSpriteSource.x;
		SDL_Rect source = { textureOffset, 0, 16, 16 };
		SDL_Rect renderQuad = { spriteBox.x, spriteBox.y, spriteBox.w, spriteBox.h };

		result.push_back(TileAnimation::RenderQuad(source, renderQuad));
	}
	break;
	}

	return result;
}
