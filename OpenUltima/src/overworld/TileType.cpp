#include "TileType.h"

TileType::TileType(int tileType, int tileWidth, int tileHeight, vector<vector<uint8_t>> definition, SDL_Renderer* renderer, 
	bool textureOrientationHorizontal) : _horizontal(textureOrientationHorizontal)
{
	_definition = definition;
	_height = tileHeight;
	_width = tileWidth;

	int textureWidth = textureOrientationHorizontal ? definition.size() * _width : _width;
	int textureHeight = !textureOrientationHorizontal ? definition.size() * _height : _height;

	_texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, textureWidth, textureHeight);
}

vector<vector<uint8_t>> TileType::getDefinition() const
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

void TileType::setRenderStrategy(shared_ptr<PixelDecodeStrategy> renderStrategy)
{
	renderTexture(renderStrategy);
}

SDL_Texture* TileType::GetTexture()
{
	return _texture;
}

void TileType::renderTexture(shared_ptr<PixelDecodeStrategy> renderStrategy) {
	auto x = 0;
	auto y = 0;
	for (auto definition : _definition) {
		SDL_Rect target = { x, y, _width, _height };
		
		// create pixel data using the render strategy
		auto pixels = renderStrategy->GetPixels(definition);
		// get a raw pointer from the vector
		auto pixelData = pixels.data();
		// write to the 2D texture, full size.
		SDL_UpdateTexture(_texture, &target, pixels.data(), _width * sizeof(uint32_t));
		// we can't clear the definition memory if we intend to be able to switch CGA/EGA renderer in runtime.

		if (_horizontal) x += _width; else y += _height;
	}
}

TileType::~TileType()
{
	if (_texture != nullptr) SDL_DestroyTexture(_texture);
	_texture = nullptr;
}