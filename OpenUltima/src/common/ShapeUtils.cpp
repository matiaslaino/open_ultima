#include "ShapeUtils.h"

shared_ptr<LTexture> ShapeUtils::arrow(SDL_Renderer* renderer, Direction direction)
{
	SDL_Texture* sdlTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 8, 8);
	shared_ptr<LTexture> texture = make_shared<LTexture>(sdlTexture, 8, 8);
	SDL_Rect target = { 0, 0, 8, 8 };

	uint32_t white = 0xFFFFFF00;
	uint32_t black = 0;
	uint32_t blue = 0x0000AF00;

	if (direction == Direction::Right) {
		uint32_t pixels[64] = {
			white,	white,	black,	black,	black,	black,	black,	black,
			blue,	blue,	white,	white,	black,	black,	black,	black,
			blue,	blue,	blue,	blue,	white,	white,	black,	black,
			blue,	blue,	blue,	blue,	blue,	blue,	white,	white,
			blue,	blue,	blue,	blue,	blue,	white,	white,	black,
			blue,	blue,	blue,	white,	white,	black,	black,	black,
			blue,	white,	white,	black,	black,	black,	black,	black,
			white,	black,	black,	black,	black,	black,	black,	black,
		};
		SDL_UpdateTexture(sdlTexture, &target, &pixels, 8 * sizeof(uint32_t));
	}
	else {
		uint32_t pixels[64] = {
			black,	black,	black,	black,	black,	black,	white,	white,
			black,	black,	black,	black,	white,	white,	blue,	blue,
			black,	black,	white,	white,	blue,	blue,	blue,	blue,
			white,	white,	blue,	blue,	blue,	blue,	blue,	blue,
			black,	white,	white,	blue,	blue,	blue,	blue,	blue,
			black,	black,	black,	white,	white,	blue,	blue,	blue,
			black,	black,	black,	black,	black,	white,	white,	blue,
			black,	black,	black,	black,	black,	black,	black,	white,
		};
		SDL_UpdateTexture(sdlTexture, &target, &pixels, 8 * sizeof(uint32_t));
	}

	return texture;
}
