#include "CGALinearRenderStrategy.h"
#include <SDL.h>
#include <vector>

using namespace std;
using namespace OpenUltima;

void LinearCGARenderStrategy::Draw(SDL_Renderer* renderer, SDL_Rect box, vector<uint8_t> bytes)
{
	int byteIndex = 0;
	for (int row = 0; row < box.h; row++) {
		for (int column = 0; column < box.w; column += 4) {
			auto byte = bytes.at(byteIndex++);

			auto pixel4 = byte & 0b00000011;
			auto pixel3 = (byte & 0b00001100) >> 2;
			auto pixel2 = (byte & 0b00110000) >> 4;
			auto pixel1 = (byte & 0b11000000) >> 6;

			DrawPixel(renderer, box.x + column, box.y + row, pixel1);
			DrawPixel(renderer, box.x + column + 1, box.y + row, pixel2);
			DrawPixel(renderer, box.x + column + 2, box.y + row, pixel3);
			DrawPixel(renderer, box.x + column + 3, box.y + row, pixel4);
		}
	}
}


void LinearCGARenderStrategy::DrawPixel(SDL_Renderer* renderer, int x, int y, int colorData) {
	if (colorData == 0b00) {
		// black
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	}
	else if (colorData == 0b11)
	{
		// white
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
	}
	else if (colorData == 0b01)
	{
		// light cyan
		SDL_SetRenderDrawColor(renderer, 0x55, 0xFF, 0xFF, 0x00);
	}
	else if (colorData == 0b10)
	{
		// light magenta
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x55, 0xFF, 0x00);
	}

	SDL_RenderDrawPoint(renderer, x, y);
}