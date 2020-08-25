#pragma once
#include "../GameObject.h"
#include <vector>
#include "Tile.h"
#include "OverworldSpriteType.h"
#include "../Player.h"
#include "Constants.h"
#include <functional>
#include "../PlayerStatusDisplay.h"
#include <map>
#include "../GameContext.h"

using namespace std;
using namespace OpenUltima;

class Overworld
{
public:
	static constexpr int DISPLAY_SIZE_TILES_WIDTH = 19;
	static constexpr int DISPLAY_SIZE_TILES_HEIGHT = 9;
	static constexpr int MAP_WIDTH_PX = DISPLAY_SIZE_TILES_WIDTH * TILE_WIDTH;
	static constexpr int MAP_HEIGHT_PX = DISPLAY_SIZE_TILES_HEIGHT * TILE_WIDTH;
	
	Overworld(shared_ptr<GameContext> context, int widthTiles, int heightTiles) : _gameContext(context)
	{
		_camera.w = DISPLAY_SIZE_TILES_WIDTH * TILE_WIDTH;
		_camera.h = DISPLAY_SIZE_TILES_HEIGHT * TILE_HEIGHT;

		setCamera();
	};

	void init(SDL_Renderer* renderer, PixelDecodeStrategy* pixelDecodeStrategy, string tilesFsPath);
	virtual void update(float elapsed);
	virtual void draw(SDL_Renderer* renderer);
	virtual void handle(const SDL_Event& event);

private:
	static constexpr int BOUND_X_TILES = 167;
	static constexpr int BOUND_Y_TILES = 155;
	static constexpr int MAP_FILE_SIZE = 13103;
	static constexpr int TILES_PER_ROW = 168;
	
	static constexpr SDL_Color COLOR_TEXT = { 0x42, 0xFF, 0xFF };

	static OverworldSpriteType::SpriteType getSpriteType(int tileTypeId);

	shared_ptr<GameContext> _gameContext;
	shared_ptr<Tile> _playerTile;
	vector<shared_ptr<Tile>> _tiles;
	SDL_Rect _camera;
	map<OverworldSpriteType::SpriteType, shared_ptr<OverworldSpriteType>> _spritesMap;

	void setCamera();
	int toPixels(int tiles);
	int toTiles(int pixels);
	void executeOnVisibleTiles(function<void(Tile*)>);
	
	void move(int deltaX, int deltaY);
	void enterDungeon();
};

