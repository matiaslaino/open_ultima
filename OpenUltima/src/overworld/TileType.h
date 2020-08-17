#pragma once
#include <cstddef>
#include <vector>
#include <SDL.h>
#include <memory>
#include "../PixelDecodeStrategy.h"
#include "../VerticalScrollingTileAnimation.h"

using namespace std;
using namespace OpenUltima;

class TileType
{
public:
	TileType(int tileType, int tileWidth, int tileHeight, vector<vector<uint8_t>> definition, SDL_Renderer* renderer, bool textureOrientationHorizontal);
	vector<vector<uint8_t>> getDefinition() const;
	int getHeight() const;
	int getWidth() const;
	void setRenderStrategy(shared_ptr<PixelDecodeStrategy> renderStrategy);
	SDL_Texture* GetTexture();
	~TileType();
	SDL_Rect getClip();
private:
	vector<vector<uint8_t>> _definition;
	int _height;
	int _width;
	SDL_Texture* _texture;
	void renderTexture(shared_ptr<PixelDecodeStrategy> renderStrategy);
	bool _horizontal = true;
};

