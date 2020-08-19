#pragma once
#include <SDL.h>
#include <vector>

using namespace std;

class PixelDecodeStrategy
{
public:
	virtual vector<uint32_t> GetPixels(vector<uint8_t> bytes) = 0;
	virtual const int getBytesPerTile() = 0;
};
