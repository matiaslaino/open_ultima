#include "TileType.h"

TileType::TileType(int tileType, int tileWidth, int tileHeight, vector<vector<uint8_t>> definition, SDL_Renderer* renderer, int animationFrames)
{
	_definition = definition;
	_height = tileHeight;
	_width = tileWidth;

	_texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, _width * animationFrames, _height);
	_animationFramesCount = animationFrames;

	for (int i = 0; i < animationFrames; i++) {
		SDL_Rect frame = { i * tileWidth, 0, tileWidth, tileHeight };
		_animationClips.push_back(frame);
	}
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
	for (auto definition : _definition) {
		SDL_Rect target = { x, 0, _width, _height };
		
		// create pixel data using the render strategy
		auto pixels = renderStrategy->GetPixels(definition);
		// get a raw pointer from the vector
		auto pixelData = pixels.data();
		// write to the 2D texture, full size.
		SDL_UpdateTexture(_texture, &target, pixels.data(), _width * sizeof(uint32_t));
		// we can't clear the definition memory if we intend to be able to switch CGA/EGA renderer in runtime.

		x += _width;
	}
}

TileType::~TileType()
{
	if (_texture != nullptr) SDL_DestroyTexture(_texture);
	_texture = nullptr;
}

SDL_Rect TileType::GetFrame(int frame) {
	return _animationClips.at(frame);
}

int TileType::GetAnimationFramesCount()
{
	return _animationFramesCount;
}

