#include "Overworld.h"
#include "../TileTypeLoader.h"
#include "../PixelDecodeStrategy.h"
#include <map>
#include "Constants.h"
#include "TileAnimation.h"

using namespace std;

void Overworld::update(float elapsed)
{
	executeOnVisibleTiles([elapsed](Tile* tile) -> void { tile->update(elapsed); });
}

void Overworld::draw(SDL_Renderer* renderer)
{
	// why do i need to declare a variable for a capture? fuck!
	auto camera = _camera;
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

		if (playerX < 0) playerX = 0;
		if (playerX > BOUND_X) playerX = BOUND_X;
		if (playerY < 0) playerY = 0;
		if (playerY > BOUND_Y) playerY = BOUND_Y;

		_player->setOverworldX(playerX);
		_player->setOverworldY(playerY);

		setCamera();
	}
}

void Overworld::init(SDL_Renderer* renderer, PixelDecodeStrategy* pixelDecodeStrategy, string tilesFsPath)
{
	_tiles.clear();

	auto spriteLoader = make_unique<TileTypeLoader>();
	auto spriteTypes = spriteLoader->loadOverworldSprites(tilesFsPath, pixelDecodeStrategy, renderer);
	map<OverworldSpriteType::SpriteType, shared_ptr<OverworldSpriteType>> spritesMap;
	for (auto spriteType : spriteTypes) {
		spritesMap.insert(pair<OverworldSpriteType::SpriteType, shared_ptr<OverworldSpriteType>>(spriteType->getType(), spriteType));
	}

	string mapFileLocation = "F:\\GOGLibrary\\Ultima 1\\MAP.BIN";
	SDL_RWops* file = SDL_RWFromFile(mapFileLocation.c_str(), "r+b");
	int mapSizeBytes = 13103;
	uint8_t* buffer = new uint8_t[mapSizeBytes];

	SDL_RWread(file, buffer, 1, mapSizeBytes);
	SDL_RWclose(file);

	auto currentX = -1;
	auto currentY = 0;

	// All water and static tiles share the same animation (water needs to scroll at the same time, and NOP tiles don't do anything)
	auto defaultSharedAnimation = make_shared<TileAnimation>();

	for (int i = 0; i < mapSizeBytes; i++) {
		auto byte = buffer[i];
		auto idTileNibble1 = byte >> 4;
		auto idTileNibble2 = byte & 0b00001111;
		auto spriteType1 = getSpriteType(idTileNibble1);
		auto spriteType2 = getSpriteType(idTileNibble2);
		auto sprite1 = spritesMap.find(spriteType1)->second;
		auto sprite2 = spritesMap.find(spriteType2)->second;
		currentX++;
		if (currentX == 168) {
			currentX = 0;
			currentY++;
		}

		auto x1 = currentX;
		auto y1 = currentY;
		if (currentX++ == 168) {
			currentX = 0;
			currentY++;
		}
		auto x2 = currentX;
		auto y2 = currentY;

		auto animation = sprite1->getAnimationType() == TileAnimation::AnimationType::SCROLLING ? defaultSharedAnimation : make_shared<TileAnimation>();
		auto tile1 = make_shared<Tile>(x1 * 16, y1 * 16, sprite1, animation);
		_tiles.push_back(tile1);

		animation = sprite2->getAnimationType() == TileAnimation::AnimationType::SCROLLING ? defaultSharedAnimation : make_shared<TileAnimation>();
		auto tile2 = make_shared<Tile>(x2 * 16, y2 * 16, sprite2, animation);
		_tiles.push_back(tile2);
	}

	delete[] buffer;
}

void Overworld::setCamera()
{
	_camera.x = toPixels(_player->getOverworldX() - (_widthTiles - 1) / 2);
	_camera.y = toPixels(_player->getOverworldY() - (_heightTiles - 1) / 2);

	int cameraBoundX = toPixels(BOUND_X);
	int cameraBoundY = toPixels(BOUND_Y);

	if (_camera.x < 0) _camera.x = 0;
	if (_camera.y < 0) _camera.y = 0;
	if (_camera.x + toPixels(_widthTiles) > cameraBoundX) _camera.x = cameraBoundX - toPixels(_widthTiles);
	if (_camera.y + toPixels(_heightTiles) > cameraBoundY) _camera.y = cameraBoundY - toPixels(_heightTiles);
}

int Overworld::toPixels(int overworldCoordinate)
{
	return overworldCoordinate * TILE_WIDTH;
}

void Overworld::executeOnVisibleTiles(function<void(Tile*)> func)
{
	int tileStartOffset = (_camera.y / TILE_WIDTH) * 168 + _camera.x / TILE_WIDTH;
	int offset = tileStartOffset;

	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 20; x++) {
			int tileOffset = (offset + x);
			if (tileOffset >= _tiles.size()) continue;

			auto tile = _tiles[tileOffset];
			func(tile.get());
		}
		offset += 168;
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