#pragma once
#include <vector>
#include <SDL.h>

using namespace std;

class TileAnimation
{
public:
	enum class AnimationType { NOP, SWAP, SCROLLING };

	struct RenderQuad {
	public:
		RenderQuad(SDL_Rect psource, SDL_Rect ptarget) : source(psource), target(ptarget) {}

		SDL_Rect source;
		SDL_Rect target;
	};

	void update(float elapsed, AnimationType animationType, SDL_Rect box);
	vector<TileAnimation::RenderQuad> getRenderQuads(SDL_Renderer* renderer, AnimationType animationType, SDL_Rect spriteBox, SDL_Rect textureSpriteSource, int swapOffset);

private:
	float _scroll = 0;
	float _swapCounter = 0;
	bool _swapped = false;
};

