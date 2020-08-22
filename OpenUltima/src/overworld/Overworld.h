#pragma once
#include "../GameObject.h"
#include <vector>
#include "Tile.h"
#include "OverworldSpriteType.h"
#include "../Player.h"
#include "Constants.h"
#include <functional>

using namespace std;
using namespace OpenUltima;

class Overworld
{
public:
	Overworld(shared_ptr<Player> player, int widthTiles, int heightTiles) : _player(player) 
	{ 
		_camera.w = DISPLAY_SIZE_TILES_WIDTH * TILE_WIDTH;
		_camera.h = DISPLAY_SIZE_TILES_HEIGHT * TILE_HEIGHT;
	
		setCamera();
	};

	virtual void update(float elapsed);
	virtual void draw(SDL_Renderer* renderer);
	virtual void handle(const SDL_Event& event);
	void init(SDL_Renderer* renderer, PixelDecodeStrategy* pixelDecodeStrategy, string tilesFsPath);

private:
	static constexpr int BOUND_X_TILES = 167;
	static constexpr int BOUND_Y_TILES = 155;
	static constexpr int MAP_FILE_SIZE = 13103;
	static constexpr int DISPLAY_SIZE_TILES_WIDTH = 19;
	static constexpr int DISPLAY_SIZE_TILES_HEIGHT = 9;
	static constexpr int TILES_PER_ROW = 168;

	shared_ptr<Player> _player;
	vector<shared_ptr<Tile>> _tiles;
	SDL_Rect _camera;
	
	static OverworldSpriteType::SpriteType getSpriteType(int tileTypeId);
	
	void setCamera();
	int toPixels(int tiles);
	int toTiles(int pixels);
	void executeOnVisibleTiles(function<void(Tile*)>);
};

