#include "Overworld.h"
#include "../TileTypeLoader.h"
#include "../PixelDecodeStrategy.h"
#include <map>
#include "Constants.h"
#include "TileAnimation.h"

using namespace std;

void Overworld::update(float elapsed)
{
	// scrolling animation (water) needs to be animated on its own.
	TileAnimation::updateScrolling(elapsed);

	executeOnVisibleTiles([elapsed](Tile* tile) -> void { tile->update(elapsed); });
}

void Overworld::draw(SDL_Renderer* renderer)
{
	// why do i need to declare a variable for a capture? fuck!
	auto camera = _camera;

	// this is a lambda expression, and i thought java was verbose!
	executeOnVisibleTiles([renderer, camera](Tile* tile) -> void { tile->draw(renderer, camera); });
}

void Overworld::handle(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		auto pressedKey = event.key.keysym.sym;
		int playerX = _player->getOverworldX();
		int playerY = _player->getOverworldY();

		switch (pressedKey)
		{
		case SDLK_UP: playerY--; break;
		case SDLK_DOWN: playerY++; break;
		case SDLK_LEFT: playerX--; break;
		case SDLK_RIGHT: playerX++; break;
		}

		// don't allow the player to move outside of overworld bounds (should this game allow world map wrapping?)
		if (playerX < 0) playerX = 0;
		if (playerX > BOUND_X_TILES) playerX = BOUND_X_TILES;
		if (playerY < 0) playerY = 0;
		if (playerY > BOUND_Y_TILES) playerY = BOUND_Y_TILES;

		_player->setOverworldX(playerX);
		_player->setOverworldY(playerY);

		// re-center camera on player if possible
		setCamera();
	}
}

void Overworld::init(SDL_Renderer* renderer, PixelDecodeStrategy* pixelDecodeStrategy, string tilesFsPath)
{
	_tiles.clear();

	// load all sprite types.
	auto spriteLoader = make_unique<TileTypeLoader>();
	auto spriteTypes = spriteLoader->loadOverworldSprites(tilesFsPath, pixelDecodeStrategy, renderer);
	
	// write to map so it's easier to find the sprite type by type name.
	map<OverworldSpriteType::SpriteType, shared_ptr<OverworldSpriteType>> spritesMap;
	for (auto spriteType : spriteTypes) {
		spritesMap.insert(pair<OverworldSpriteType::SpriteType, shared_ptr<OverworldSpriteType>>(spriteType->getType(), spriteType));
	}

	// TODO: get this from parameter.
	string mapFileLocation = "F:\\GOGLibrary\\Ultima 1\\MAP.BIN";
	
	SDL_RWops* file = SDL_RWFromFile(mapFileLocation.c_str(), "r+b");
	uint8_t* buffer = new uint8_t[MAP_FILE_SIZE];
	SDL_RWread(file, buffer, 1, MAP_FILE_SIZE);
	SDL_RWclose(file);

	auto currentX = -1;
	auto currentY = 0;

	// All water and static tiles share the same animation (water needs to scroll at the same time, and NOP tiles don't do anything)
	auto defaultSharedAnimation = make_shared<TileAnimation>();

	// map file format is one byte contains the data of two tiles, one per nibble, so shift and mask them.
	for (int i = 0; i < MAP_FILE_SIZE; i++) {
		auto byte = buffer[i];
		auto idTileNibble1 = byte >> 4;
		auto idTileNibble2 = byte & 0b00001111;
		auto spriteType1 = getSpriteType(idTileNibble1);
		auto spriteType2 = getSpriteType(idTileNibble2);
		auto sprite1 = spritesMap.find(spriteType1)->second;
		auto sprite2 = spritesMap.find(spriteType2)->second;
		
		currentX++;
		if (currentX > BOUND_X_TILES) {
			currentX = 0;
			currentY++;
		}
		auto x1 = currentX;
		auto y1 = currentY;
		
		currentX++;
		if (currentX > BOUND_X_TILES) {
			currentX = 0;
			currentY++;
		}
		auto x2 = currentX;
		auto y2 = currentY;

		// water tiles share the same scrolling animation instance so they all animate at the same time
		auto animation = sprite1->getAnimationType() == TileAnimation::AnimationType::SCROLLING ? defaultSharedAnimation : make_shared<TileAnimation>();
		auto tile1 = make_shared<Tile>(toPixels(x1), toPixels(y1), sprite1, animation);
		_tiles.push_back(tile1);

		animation = sprite2->getAnimationType() == TileAnimation::AnimationType::SCROLLING ? defaultSharedAnimation : make_shared<TileAnimation>();
		auto tile2 = make_shared<Tile>(toPixels(x2), toPixels(y2), sprite2, animation);
		_tiles.push_back(tile2);
	}

	delete[] buffer;
}

void Overworld::setCamera()
{
	_camera.x = toPixels(_player->getOverworldX() - (DISPLAY_SIZE_TILES_WIDTH - 1) / 2);
	_camera.y = toPixels(_player->getOverworldY() - (DISPLAY_SIZE_TILES_HEIGHT - 1) / 2);

	int cameraBoundX = toPixels(BOUND_X_TILES);
	int cameraBoundY = toPixels(BOUND_Y_TILES);

	// make sure the camera doesn't show where the world ends!
	if (_camera.x < 0) _camera.x = 0;
	if (_camera.y < 0) _camera.y = 0;
	if (_camera.x + toPixels(DISPLAY_SIZE_TILES_WIDTH) > cameraBoundX) _camera.x = cameraBoundX - toPixels(DISPLAY_SIZE_TILES_WIDTH);
	if (_camera.y + toPixels(DISPLAY_SIZE_TILES_HEIGHT) > cameraBoundY) _camera.y = cameraBoundY - toPixels(DISPLAY_SIZE_TILES_HEIGHT);
}

int Overworld::toPixels(int tiles)
{
	return tiles * TILE_WIDTH;
}

int Overworld::toTiles(int pixels)
{
	return pixels / TILE_WIDTH;
}

void Overworld::executeOnVisibleTiles(function<void(Tile*)> func)
{
	int tileStartOffset = toTiles(_camera.y) * TILES_PER_ROW + toTiles(_camera.x);
	int offset = tileStartOffset;

	for (int y = 0; y < DISPLAY_SIZE_TILES_HEIGHT; y++) {
		for (int x = 0; x < DISPLAY_SIZE_TILES_WIDTH; x++) {
			int tileOffset = (offset + x);
			if (tileOffset >= _tiles.size()) continue;

			auto tile = _tiles[tileOffset];
			func(tile.get());
		}
		offset += TILES_PER_ROW;
	}
}

OverworldSpriteType::SpriteType Overworld::getSpriteType(int tileTypeId) {
	switch (tileTypeId) {
	case 0:
	{ return OverworldSpriteType::SpriteType::WATER; }
	break;
	case 1:
	{ return OverworldSpriteType::SpriteType::GRASS; }
	break;
	case 2:
	{ return OverworldSpriteType::SpriteType::FOREST; }
	break;
	case 3:
	{ return OverworldSpriteType::SpriteType::MOUNTAIN; }
	break;
	case 4:
	{ return OverworldSpriteType::SpriteType::CASTLE; }
	break;
	case 5:
	{ return OverworldSpriteType::SpriteType::SIGNPOST; }
	break;
	case 6:
	{ return OverworldSpriteType::SpriteType::TOWN; }
	break;
	case 7:
	{ return OverworldSpriteType::SpriteType::DUNGEON_ENTRANCE; }
	break;
	}

	throw "Error!";
}