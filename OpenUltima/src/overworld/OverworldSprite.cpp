#include "OverworldSprite.h"
#include "Constants.h"

OverworldSprite::OverworldSprite(shared_ptr<LTexture> overworldTexture, int textureOffset, int swapOffset)
	: _texture(overworldTexture), _textureOffset(textureOffset), _swapOffset(swapOffset)
{
	_source = { textureOffset, 0, 16, 16 };
	_animationType = AnimationType::SWAP;
}

OverworldSprite::OverworldSprite(shared_ptr<LTexture> overworldTexture, int textureOffset, bool scroll)
	: _texture(overworldTexture), _textureOffset(textureOffset)
{
	_source = { textureOffset, 0, 16, 16 };
	_animationType = scroll ? AnimationType::SCROLLING : AnimationType::NOP;
}

shared_ptr<LTexture> OverworldSprite::getTexture()
{
	return _texture;
}

SDL_Rect OverworldSprite::getSource()
{
	return _source;
}

OverworldSprite::AnimationType OverworldSprite::getAnimationType()
{
	return _animationType;
}

int OverworldSprite::swapOffset()
{
	return _swapOffset;
}
