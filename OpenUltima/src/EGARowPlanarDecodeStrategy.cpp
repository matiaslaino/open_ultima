#include "EGARowPlanarDecodeStrategy.h"

using namespace OpenUltima;

uint32_t EGARowPlanarDecodeStrategy::GetPixel(int colorData) {
	// EGA palette is 16 colors only.
	switch (colorData) {
	case 1:
		// blue
		return 0x0000A800;
		break;
	case 2:
		// green
		return 0x00A80000;
		break;
	case 3:
		// cyan
		return 0x00A8A800;
		break;
	case 4:
		// red
		return 0xA8000000;
		break;
	case 5:
		// magenta
		return 0xA800A800;
		break;
	case 6:
		// orange
		return 0xA8540000;
		break;
	case 7:
		// grey
		return 0xA8A8A800;
		break;
	case 8:
		// dark grey
		return 0x54545400;
		break;
	case 9:
		// light blue
		return 0x5454FE00;
		break;
	case 10:
		// light green
		return 0x54FE5400;
		break;
	case 11:
		// light cyan
		return 0x54FEFE00;
		break;
	case 12:
		// bright red
		return 0xFE545400;
		break;
	case 13:
		// bright magenta
		return 0xFE54FE00;
		break;
	case 14:
		// yellow
		return 0xFEFE5400;
		break;
	case 15:
		// white
		return 0xFEFEFEFE;
		break;
	default:
		// black
		return 0x00000000;
	}
}

vector<uint32_t> OpenUltima::EGARowPlanarDecodeStrategy::GetPixels(vector<uint8_t> bytes)
{
	vector<uint32_t> pixels;
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

	//const int bytesPerPlane = box.w / 8;
	const int bytesPerPlane = 2;

	for (auto byte : bytes) {
		byteIndex++;
		byteIndex %= bytesPerPlane;
		if (byteIndex == 0) {
			componentIndex++;
			componentIndex %= PLANES_COUNT;
		}

		vector<bool>& component = components.at(componentIndex);

		component.push_back((byte & 0b10000000) >> 7);
		component.push_back((byte & 0b01000000) >> 6);
		component.push_back((byte & 0b00100000) >> 5);
		component.push_back((byte & 0b00010000) >> 4);
		component.push_back((byte & 0b00001000) >> 3);
		component.push_back((byte & 0b00000100) >> 2);
		component.push_back((byte & 0b00000010) >> 1);
		component.push_back((byte & 0b00000001) >> 0);
	}


	for (auto i = 0; i < 256; i++)
	{
		int paletteIndex = blue[i] + green[i] * 2 + red[i] * 4 + intensity[i] * 8;
		auto pixel = GetPixel(paletteIndex);
		pixels.push_back(pixel);
	}

	return pixels;
}