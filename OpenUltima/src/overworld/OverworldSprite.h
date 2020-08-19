#pragma once
#include <SDL.h>
#include <memory>
#include "../common/LTexture.h"

using namespace std;

class OverworldSprite
{
public:
	enum class AnimationType { NOP, SWAP, SCROLLING };

	OverworldSprite(shared_ptr<LTexture> overworldTexture, int textureOffset, int swapOffset);
	OverworldSprite(shared_ptr<LTexture> overworldTexture, int textureOffset, bool scroll);
	shared_ptr<LTexture> getTexture();
	SDL_Rect getSource();
	AnimationType getAnimationType();
	int swapOffset();
private:
	shared_ptr<LTexture> _texture;
	int _textureOffset;
	SDL_Rect _source;
	AnimationType _animationType;
	int _swapOffset;
};

