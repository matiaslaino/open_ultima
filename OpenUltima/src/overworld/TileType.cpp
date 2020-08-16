#include "TileType.h"

TileType::TileType(int tileType, int tileWidth, int tileHeight, vector<uint8_t> definition)
{
	_definition = definition;
	_height = tileHeight;
	_width = tileWidth;

}

TileType::TileType(int tileType, int tileWidth, int tileHeight, vector<uint8_t> definition, SDL_Renderer* renderer)
{
	_definition = definition;
	_height = tileHeight;
	_width = tileWidth;

	_texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, _width, _height);
}


vector<uint8_t> TileType::getDefinition() const
{
	return _definition;
}

int TileType::getHeight() const
{
	return _height;
}

int TileType::getWidth() const
{
	return _width;
}

void TileType::setRenderStrategy(shared_ptr<TileRenderStrategy> renderStrategy)
{
	renderTexture(renderStrategy);
}

SDL_Texture* TileType::GetTexture()
{
	return _texture;
}

void TileType::renderTexture(shared_ptr<TileRenderStrategy> renderStrategy) {
	auto pixels = renderStrategy->GetPixels(_definition);
	auto pixelData = pixels.data();
	SDL_UpdateTexture(_texture, NULL, pixels.data(), _width * sizeof(uint32_t));
}