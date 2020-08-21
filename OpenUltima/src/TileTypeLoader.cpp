#include "TileTypeLoader.h"
#include "overworld/Constants.h"

vector<shared_ptr<OverworldSpriteType>> TileTypeLoader::loadOverworldSprites(string tilesFileLocation, PixelDecodeStrategy* pixelDecodeStrategy, SDL_Renderer* renderer)
{
	// Tile definition file contains 52 different tiles, some are actually the animated portion of another tile (castle with flag up, and with flag down).
	SDL_RWops* file = SDL_RWFromFile(tilesFileLocation.c_str(), "r+b");
	//SDL_RWseek(file, (uint64_t)pixelDecodeStrategy->getBytesPerTile() * 4, RW_SEEK_SET);

	auto overworldTexture = loadTexture(file, pixelDecodeStrategy, renderer, 52, 16, 16);

	vector< shared_ptr<OverworldSpriteType>> result;

	int spriteOffset = 16;

	// Water
	int currentOffset = 0;
	auto sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::WATER, overworldTexture, currentOffset, true);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Grass
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::GRASS,overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Forest
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::FOREST, overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Mountain
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::MOUNTAIN, overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Castle
	auto swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::CASTLE, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// Signpost
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::SIGNPOST, overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Town
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::TOWN, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// Dungeon Entrance
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::DUNGEON_ENTRANCE, overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Player
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::PLAYER, overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Horse
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::HORSE, overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Cart
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::CART, overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Raft
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::RAFT, overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Pirate Ship
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::FRIGATE, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// Airship
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::AIRCAR, overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Shuttle
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::SHUTTLE, overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Time Machine
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::TIME_MACHINE, overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Ness
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::NESS_MONSTER, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// Squid
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::GIANT_SQUID, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;
	
	// Dragon Turtle
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::DRAGON_TURTLE, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;
	
	// 
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::PIRATE_SHIP, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// 
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::HOOD, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;
	
	// 
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::BEAR, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// 
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::HIDDEN_ARCHER, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// 
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::DARK_KNIGHT, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// 
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::EVIL_TRENT, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// 
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::THIEF, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// 
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::ORC, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// 
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::KNIGHT, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// 
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::NECROMANCER, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// 
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::EVIL_RANGER, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSpriteType>(OverworldSpriteType::SpriteType::WANDERING_WARLOCK, overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;
	
	SDL_RWclose(file);

	return result;
}

shared_ptr<LTexture> TileTypeLoader::loadTexture(SDL_RWops* file, PixelDecodeStrategy* pixelDecodeStrategy, SDL_Renderer* renderer, int spriteCount, int spriteWidth, int spriteHeight) {
	uint64_t tileBytesCount = (uint64_t)pixelDecodeStrategy->getBytesPerTile();
	shared_ptr<uint8_t[]> buffer(new uint8_t[tileBytesCount * spriteCount]);

	SDL_RWread(file, buffer.get(), 1, tileBytesCount * spriteCount);

	int textureWidth = spriteWidth * spriteCount;
	int textureHeight = spriteHeight;

	SDL_Texture* sdlTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, textureWidth, textureHeight);
	shared_ptr<LTexture> texture = make_shared<LTexture>(sdlTexture, textureWidth, textureHeight);

	auto startIndex = 0;
	auto bytesPerTile = pixelDecodeStrategy->getBytesPerTile();
	for (int spriteIndex = 0; spriteIndex < spriteCount; spriteIndex++) {
		auto rawPointer = buffer.get();
		auto spriteBytes = vector(rawPointer + startIndex, rawPointer + startIndex + bytesPerTile);
		auto pixels = pixelDecodeStrategy->GetPixels(spriteBytes);

		SDL_Rect target = { spriteIndex * spriteWidth, 0, spriteWidth, spriteHeight };

		auto pixelData = pixels.data();
		SDL_UpdateTexture(sdlTexture, &target, pixels.data(), spriteWidth * sizeof(uint32_t));
		startIndex += bytesPerTile;
	}

	return texture;
}