#include <cstddef>
#include <memory>
#include <vector>

#include "Tile.h"

using namespace std;
using namespace OpenUltima;

Tile::Tile(int x, int y, shared_ptr<OverworldSpriteType> sprite)
	: _sprite(sprite)
{
	_box.x = x;
	_box.y = y;

	_box.w = TILE_WIDTH;
	_box.h = TILE_HEIGHT;
}

void Tile::draw(SDL_Renderer* renderer, SDL_Rect camera) {
	if (isVisible(camera)) {
		auto animation = _sprite->getAnimationType();

		auto renderQuads = _sprite->getTileAnimation()->getRenderQuads(renderer, _sprite->getAnimationType(), _box, _sprite->getSource(), _sprite->swapOffset());

		for (auto renderQuad : renderQuads) {
			SDL_Rect adjustedRenderTargetQuad = { renderQuad.target.x - camera.x, renderQuad.target.y - camera.y, renderQuad.target.w, renderQuad.target.h };
			SDL_RenderCopyEx(renderer, _sprite->getTexture().get()->getRawTexture(), &renderQuad.source, &adjustedRenderTargetQuad, 0, NULL, SDL_FLIP_NONE);
		}
	}
}

void OpenUltima::Tile::update(float elapsed)
{
	_sprite->getTileAnimation()->update(elapsed, _sprite->getAnimationType(), _box);
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