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
	Overworld(shared_ptr<Player> player, int widthTiles, int heightTiles) : _player(player), _widthTiles(widthTiles), _heightTiles(heightTiles) 
	{ 
		_camera.w = 19 * TILE_WIDTH;
		_camera.h = 9 * TILE_HEIGHT;
	
		setCamera();
	};

	virtual void update(float elapsed);
	virtual void draw(SDL_Renderer* renderer);
	virtual void handle(const SDL_Event& event);
	void init(SDL_Renderer* renderer, PixelDecodeStrategy* pixelDecodeStrategy, string tilesFsPath);

private:
	static constexpr int BOUND_X = 167;
	static constexpr int BOUND_Y = 155;

	shared_ptr<Player> _player;
	vector<shared_ptr<Tile>> _tiles;
	SDL_Rect _camera;
	int _widthTiles;
	int _heightTiles;

	static OverworldSpriteType::SpriteType getSpriteType(int tileTypeId);

	void setCamera();
	int toPixels(int overworldCoordinate);
	void executeOnVisibleTiles(function<void(Tile*)>);
};

