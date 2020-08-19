#include "TileTypeLoader.h"

vector<shared_ptr<OverworldSprite>> TileTypeLoader::loadOverworldSprites(string tilesFileLocation, PixelDecodeStrategy* pixelDecodeStrategy, SDL_Renderer* renderer)
{
	// Tile definition file contains 52 different tiles, some are actually the animated portion of another tile (castle with flag up, and with flag down).
	SDL_RWops* file = SDL_RWFromFile(tilesFileLocation.c_str(), "r+b");
	//SDL_RWseek(file, (uint64_t)pixelDecodeStrategy->getBytesPerTile() * 4, RW_SEEK_SET);

	auto overworldTexture = loadTexture(file, pixelDecodeStrategy, renderer, 52, 16, 16);

	vector< shared_ptr<OverworldSprite>> result;

	int spriteOffset = 16;

	// Water
	int currentOffset = 0;
	auto sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, true);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Grass
	sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Forest
	sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Mountain
	sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Castle
	auto swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// Signpost
	sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Town
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// Dungeon Entrance
	sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Player
	sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Horse
	sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Cart
	sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Raft
	sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Pirate Ship
	swapOffset = currentOffset + spriteOffset;
	sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, swapOffset);
	result.push_back(sprite);
	currentOffset += 2 * spriteOffset;

	// Airship
	sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

	// Shuttle
	sprite = make_shared<OverworldSprite>(overworldTexture, currentOffset, false);
	result.push_back(sprite);
	currentOffset += spriteOffset;

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