#include "EGARowPlanarRenderStrategy.h"

using namespace OpenUltima;

void EGARowPlanarRenderStrategy::Draw(SDL_Renderer* renderer, SDL_Rect box, vector<uint8_t> bytes)
{
	/*
		EGA row-planar stores pixel color information coded in "planes".
		A plane is either blue / green / red or intensity, with the information from all the planes you can draw the correct color.
		A pure red pixel will just have a "1" on the red plane, and 0s on the rest of the planes. Intensity just makes it brighter or dimmer.
		Each sprite is coded in sequence, and this format will save the sprite pixel information (all planes) row per row.
		So if a sprite is 16 pixels wide (each row is 16 px long), then EGA row-planar will use 2 whole byte for the blue information for the first 16 bits.
		After the blue color, we will have 2 more bytes for red, 2 more bytes for green, and 2 more for intensity.
		This means in total it will use 2(bytes)x4(planes) = 8 bytes per each of the sprite's rows.
		If our sprite is 16x16, that's 16 rows, then it will take 8 (bytes per row) x 16 (rows) = 128 bytes per sprite.

				0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15   <----- pixel position
		blue	0	0	0	0	0	0	0	0	1	1	1	1	1	1	1	1
		green	2	2	2	2	2	2	2	2	3	3	3	3	3	3	3	3
		red		4	4	4	4	4	4	4	4	5	5	5	5	5	5	5	5
		inten	6	6	6	6	6	6	6	6	7	7	7	7	7	7	7	7	
				^
				|
				byte offset

	*/

	vector<bool> blue;
	vector<bool> green;
	vector<bool> red;
	vector<bool> intensity;

	// In Ultima1, the planes are stored in the order BGRI
	vector<reference_wrapper<vector<bool>>> components = { blue, green, red, intensity };
	int componentIndex = -1;
	int byteIndex = -1;
	
	const int bytesPerPlane = box.w / 8;

	for (auto byte : bytes) {		
		byteIndex++;
		byteIndex %= bytesPerPlane;
		if (byteIndex == 0) {
			componentIndex++;
			componentIndex %= PLANES_COUNT;
		}
		
		vector<bool> & component = components.at(componentIndex);

		component.push_back((byte & 0b10000000) >> 7);
		component.push_back((byte & 0b01000000) >> 6);
		component.push_back((byte & 0b00100000) >> 5);
		component.push_back((byte & 0b00010000) >> 4);
		component.push_back((byte & 0b00001000) >> 3);
		component.push_back((byte & 0b00000100) >> 2);
		component.push_back((byte & 0b00000010) >> 1);
		component.push_back((byte & 0b00000001) >> 0);
	}
	
	int pixelIndex = 0;
	for (auto row = 0; row < box.h; row++)
	{
		for (auto column = 0; column < box.w; column++)
		{
			int paletteIndex = blue[pixelIndex] + green[pixelIndex] * 2 + red[pixelIndex] * 4 + intensity[pixelIndex] * 8;
			DrawPixel(renderer, box.x + column, box.y + row, paletteIndex);
			pixelIndex++;
		}
	}
}

void EGARowPlanarRenderStrategy::DrawPixel(SDL_Renderer* renderer, int x, int y, int colorData) {
	// EGA palette is 16 colors only.
	switch (colorData) {
	case 0:
		// black
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		break;
	case 1:
		// blue
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xA8, 0x00);
		break;
	case 2:
		// green
		SDL_SetRenderDrawColor(renderer, 0x00, 0xA8, 0x00, 0x00);
		break;
	case 3:
		// cyan
		SDL_SetRenderDrawColor(renderer, 0x00, 0xA8, 0xA8, 0x00);
		break;
	case 4:
		// red
		SDL_SetRenderDrawColor(renderer, 0xA8, 0x00, 0x00, 0x00);
		break;
	case 5:
		// magenta
		SDL_SetRenderDrawColor(renderer, 0xA8, 0x00, 0xA8, 0x00);
		break;
	case 6:
		// orange
		SDL_SetRenderDrawColor(renderer, 0xA8, 0x54, 0x00, 0x00);
		break;
	case 7:
		// grey
		SDL_SetRenderDrawColor(renderer, 0xA8, 0xA8, 0xA8, 0x00);
		break;
	case 8:
		// dark grey
		SDL_SetRenderDrawColor(renderer, 0x54, 0x54, 0x54, 0x00);
		break;
	case 9:
		// light blue
		SDL_SetRenderDrawColor(renderer, 0x54, 0x54, 0xFE, 0x00);
		break;
	case 10:
		// light green
		SDL_SetRenderDrawColor(renderer, 0x54, 0xFE, 0x54, 0x00);
		break;
	case 11:
		// light cyan
		SDL_SetRenderDrawColor(renderer, 0x54, 0xFE, 0xFE, 0x00);
		break;
	case 12:
		// bright red
		SDL_SetRenderDrawColor(renderer, 0xFE, 0x54, 0x54, 0x00);
		break;
	case 13:
		// bright magenta
		SDL_SetRenderDrawColor(renderer, 0xFE, 0x54, 0xFE, 0x00);
		break;
	case 14:
		// yellow
		SDL_SetRenderDrawColor(renderer, 0xFE, 0xFE, 0x54, 0x00);
		break;
	case 15:
		// white
		SDL_SetRenderDrawColor(renderer, 0xFE, 0xFE, 0xFE, 0xFE);
		break;
	}
	
	SDL_RenderDrawPoint(renderer, x, y);
}