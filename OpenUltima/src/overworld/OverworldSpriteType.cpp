#include "OverworldSpriteType.h"

#include <utility>
#include "Constants.h"

OverworldSpriteType::OverworldSpriteType(SpriteType type, shared_ptr<LTexture> overworldTexture, int textureOffset,
                                         int swapOffset)
        : _texture(std::move(overworldTexture)), _textureOffset(textureOffset), _swapOffset(swapOffset), _type(type) {
    _source = {textureOffset, 0, SPRITE_SIZE, SPRITE_SIZE};
    _animationType = TileAnimation::AnimationType::SWAP;
}

OverworldSpriteType::OverworldSpriteType(SpriteType type, shared_ptr<LTexture> overworldTexture, int textureOffset,
                                         bool scroll)
        : _texture(std::move(overworldTexture)), _textureOffset(textureOffset), _type(type), _swapOffset(-1) {
    _source = {textureOffset, 0, SPRITE_SIZE, SPRITE_SIZE};
    _animationType = scroll ? TileAnimation::AnimationType::SCROLLING : TileAnimation::AnimationType::NOP;
}

shared_ptr<LTexture> OverworldSpriteType::getTexture() {
    return _texture;
}

SDL_Rect OverworldSpriteType::getSource() {
    return _source;
}

int OverworldSpriteType::getSwapOffset() const {
    return _swapOffset;
}

TileAnimation::AnimationType OverworldSpriteType::getAnimationType() {
    return _animationType;
}

OverworldSpriteType::SpriteType OverworldSpriteType::getType() {
    return _type;
}