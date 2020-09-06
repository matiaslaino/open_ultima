#pragma once

#include <SDL.h>
#include <vector>

using namespace std;

class PixelDecodeStrategy {
public:
    PixelDecodeStrategy(int tileWidth, int tileHeight) : _tileWidth(tileWidth), _tileHeight(tileHeight) {}

    virtual vector<uint32_t> GetPixels(vector<uint8_t> bytes) = 0;

    virtual int getBytesPerTile() = 0;

protected:
    int _tileWidth;
    int _tileHeight;
};
