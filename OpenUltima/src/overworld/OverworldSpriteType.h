#pragma once
#include <SDL.h>
#include <memory>
#include "../common/LTexture.h"
#include "Constants.h"
#include "TileAnimation.h"

using namespace std;

class OverworldSpriteType
{
public:
	enum class SpriteType {
		WATER, GRASS, FOREST, MOUNTAIN, CASTLE, SIGNPOST, TOWN, DUNGEON_ENTRANCE, PLAYER, HORSE, CART, RAFT, FRIGATE, AIRCAR, SHUTTLE,
		TIME_MACHINE, NESS_MONSTER, GIANT_SQUID, DRAGON_TURTLE, PIRATE_SHIP, HOOD, BEAR, HIDDEN_ARCHER, DARK_KNIGHT, EVIL_TRENT, THIEF, ORC, KNIGHT, NECROMANCER, EVIL_RANGER, WANDERING_WARLOCK
	};

	OverworldSpriteType(SpriteType type, shared_ptr<LTexture> overworldTexture, int textureOffset, int swapOffset);
	OverworldSpriteType(SpriteType type, shared_ptr<LTexture> overworldTexture, int textureOffset, bool scroll);
	shared_ptr<LTexture> getTexture();
	SDL_Rect getSource();
	int swapOffset();
	SpriteType getType();
	TileAnimation::AnimationType getAnimationType();
private:
	shared_ptr<LTexture> _texture;
	int _textureOffset;
	SDL_Rect _source;
	TileAnimation::AnimationType _animationType;
	int _swapOffset;
	SpriteType _type;
};

