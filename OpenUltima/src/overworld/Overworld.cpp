#include "Overworld.h"
#include "../TileTypeLoader.h"
#include "../EGARowPlanarDecodeStrategy.h"
#include <map>
#include "Constants.h"

using namespace std;

void Overworld::update(float elapsed)
{
	int tileStartOffset = (_player->getOverworldY()) * 168 + _player->getOverworldX();
	int offset = tileStartOffset;

	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 20; x++) {
			int tileOffset = offset + x;
			auto tile = _tiles[tileOffset];
			tile->update(elapsed);
		}
		offset += 168;
	}
}

void Overworld::draw(SDL_Renderer* renderer)
{
	int tileStartOffset = (_player->getOverworldY()) * 168 + _player->getOverworldX();
	int offset = tileStartOffset;

	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 20; x++) {
			int tileOffset = offset + x;
			auto tile = _tiles[tileOffset];
			tile->draw(renderer, _camera);
		}
		offset += 168;
	}
}

void Overworld::handle(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		auto pressedKey = event.key.keysym.sym;
		int playerX = _player->getOverworldX();
		int playerY = _player->getOverworldY();

		switch (pressedKey)
		{
		case SDLK_UP: _player->setOverworldY(--playerY); break;
		case SDLK_DOWN: _player->setOverworldY(++playerY); break;
		case SDLK_LEFT: _player->setOverworldX(--playerX); break;
		case SDLK_RIGHT: _player->setOverworldX(++playerX); break;
		}

		setCamera();
	}
}

void Overworld::init(SDL_Renderer* renderer)
{
	auto spriteLoader = make_unique<TileTypeLoader>();
	auto spriteTypes = spriteLoader->loadOverworldSprites("F:\\GOGLibrary\\Ultima 1\\EGATILES.BIN", make_unique< EGARowPlanarDecodeStrategy>().get(), renderer);
	map<OverworldSpriteType::SpriteType, shared_ptr<OverworldSpriteType>> spritesMap;
	for (auto spriteType : spriteTypes) {
		spritesMap.insert(pair<OverworldSpriteType::SpriteType, shared_ptr<OverworldSpriteType>>(spriteType->getType(), spriteType));
	}

	string mapFileLocation = "F:\\GOGLibrary\\Ultima 1\\MAP.BIN";
	SDL_RWops* file = SDL_RWFromFile(mapFileLocation.c_str(), "r+b");
	int mapSizeBytes = 13088;
	uint8_t* buffer = new uint8_t[mapSizeBytes];

	SDL_RWread(file, buffer, 1, mapSizeBytes);
	SDL_RWclose(file);

	auto currentX = -1;
	auto currentY = 0;
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

		auto tile1 = make_shared<Tile>(x1 * 16, y1 * 16, sprite1);
		auto tile2 = make_shared<Tile>(x2 * 16, y2 * 16, sprite2);

		_tiles.push_back(tile1);
		_tiles.push_back(tile2);
	}

	delete[] buffer;
}

vector<Tile> Overworld::getMap(int x, int y, int widthTiles, int heightTiles)
{
	return vector<Tile>();
}

void Overworld::setCamera()
{
	_camera.x = _player->getOverworldX() * TILE_WIDTH - (int)(_widthTiles / 2);
	_camera.y = _player->getOverworldY() * TILE_HEIGHT - (int)(_heightTiles / 2);

	if (_camera.x < 0) _camera.x = 0;
	if (_camera.y < 0) _camera.y = 0;
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