#include <cstddef>
#include <memory>

#include "Tile.h"

using namespace std;
using namespace OpenUltima;

Tile::Tile(int x, int y, shared_ptr<OverworldSprite> sprite)
	: _sprite(sprite)
{
	_box.x = x;
	_box.y = y;

	_box.w = TILE_WIDTH;
	_box.h = TILE_HEIGHT;
}

void Tile::draw(SDL_Renderer* renderer, SDL_Rect camera) {
	if (isVisible(camera)) {

		switch (_sprite->getAnimationType()) {
		case OverworldSprite::AnimationType::NOP:
		{
			SDL_Rect renderQuadNop = { _box.x - camera.x, _box.y - camera.y, _box.w, _box.h };
			SDL_RenderCopyEx(renderer, _sprite->getTexture().get()->getRawTexture(), &_sprite->getSource(), &renderQuadNop, 0, NULL, SDL_FLIP_NONE);
		}
		break;
		case OverworldSprite::AnimationType::SCROLLING: 
		{
			// TODO check copy of rect
			int scrollOffset = (int)_scroll;

			SDL_Rect upperPortionSource = { _sprite->getSource().x, 0, 16, scrollOffset };
			SDL_Rect lowerPortionSource = { _sprite->getSource().x, scrollOffset, 16, _box.h - scrollOffset };
			SDL_Rect upperRenderQuad = { _box.x - camera.x, _box.y - camera.y, _box.w, _box.h - scrollOffset };
			SDL_Rect lowerRenderQuad = { _box.x - camera.x, _box.y - camera.y + _box.h - scrollOffset, _box.w, scrollOffset };

			SDL_RenderCopyEx(renderer, _sprite->getTexture().get()->getRawTexture(), &lowerPortionSource, &upperRenderQuad, 0, NULL, SDL_FLIP_NONE);
			SDL_RenderCopyEx(renderer, _sprite->getTexture().get()->getRawTexture(), &upperPortionSource, &lowerRenderQuad, 0, NULL, SDL_FLIP_NONE);
		}
													  break;
		case OverworldSprite::AnimationType::SWAP:
		{
			int textureOffset = _swapped ? _sprite->swapOffset() : _sprite->getSource().x;
			SDL_Rect source = { textureOffset, 0, 16, 16 };
			SDL_Rect renderQuad = { _box.x - camera.x, _box.y - camera.y, _box.w, _box.h };
			SDL_RenderCopyEx(renderer, _sprite->getTexture().get()->getRawTexture(), &source, &renderQuad, 0, NULL, SDL_FLIP_NONE);
		}
		break;
		}
	}
}

void OpenUltima::Tile::update(float elapsed)
{
	switch (_sprite->getAnimationType()) {
	case OverworldSprite::AnimationType::NOP:
		break;
	case OverworldSprite::AnimationType::SCROLLING:
		_scroll += (_box.h / 2) * elapsed;
		if (_scroll >= _box.h) _scroll = 0;
		break;
	case OverworldSprite::AnimationType::SWAP:
		_swapCounter += elapsed;

		if (_swapCounter >= 3) {
			_swapCounter = 0;
			_swapped = !_swapped;
		}
		break;
	}
}

bool Tile::isVisible(SDL_Rect camera)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = _box.x;
	rightA = _box.x + _box.w;
	topA = _box.y;
	bottomA = _box.y + _box.h;

	//Calculate the sides of rect B
	leftB = camera.x;
	rightB = camera.x + camera.w;
	topB = camera.y;
	bottomB = camera.y + camera.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}