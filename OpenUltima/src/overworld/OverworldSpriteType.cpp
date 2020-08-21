#include "OverworldSpriteType.h"
#include "Constants.h"

OverworldSpriteType::OverworldSpriteType(SpriteType type, shared_ptr<LTexture> overworldTexture, int textureOffset, int swapOffset)
	: _texture(overworldTexture), _textureOffset(textureOffset), _swapOffset(swapOffset), _type(type)
{
	_source = { textureOffset, 0, 16, 16 };
	_animationType = TileAnimation::AnimationType::SWAP;
	_tileAnimation = make_shared<TileAnimation>();
	;
}

OverworldSpriteType::OverworldSpriteType(SpriteType type, shared_ptr<LTexture> overworldTexture, int textureOffset, bool scroll)
	: _texture(overworldTexture), _textureOffset(textureOffset), _type(type), _swapOffset(-1)
{
	_source = { textureOffset, 0, 16, 16 };
	_animationType = scroll ? TileAnimation::AnimationType::SCROLLING : TileAnimation::AnimationType::NOP;
	_tileAnimation = make_shared<TileAnimation>();
}

shared_ptr<LTexture> OverworldSpriteType::getTexture()
{
	return _texture;
}

SDL_Rect OverworldSpriteType::getSource()
{
	return _source;
}

int OverworldSpriteType::swapOffset()
{
	return _swapOffset;
}

TileAnimation::AnimationType OverworldSpriteType::getAnimationType()
{
	return _animationType;
}

OverworldSpriteType::SpriteType OverworldSpriteType::getType()
{
	return _type;
}

shared_ptr<TileAnimation> OverworldSpriteType::getTileAnimation()
{
	return _tileAnimation;
}