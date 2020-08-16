#pragma once
#include <cstddef>
#include <vector>
#include <SDL.h>
#include <memory>
#include "../TileRenderStrategy.h"

using namespace std;
using namespace OpenUltima;

class TileType
{
public:
	TileType(int tileType, int tileWidth, int tileHeight, vector<uint8_t> definition);
	TileType(int tileType, int tileWidth, int tileHeight, vector<uint8_t> definition, SDL_Renderer* renderer);
	vector<uint8_t> getDefinition() const;
	int getHeight() const;
	int getWidth() const;
	void setRenderStrategy(shared_ptr<TileRenderStrategy> renderStrategy);
	SDL_Texture* GetTexture();
	~TileType();

private:
	vector<uint8_t> _definition;
	int _height;
	int _width;
	SDL_Texture* _texture;
	void renderTexture(shared_ptr<TileRenderStrategy> renderStrategy);
};

