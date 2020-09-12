#pragma once

#include "PixelDecodeStrategy.h"

class EGARowPlanarDecodeStrategy :
        public PixelDecodeStrategy {
public:
    EGARowPlanarDecodeStrategy(int tileWidth, int tileHeight) : PixelDecodeStrategy(tileWidth, tileHeight) {}

    vector<uint32_t> GetPixels(vector<uint8_t> bytes) override;

private:
    static constexpr int PLANES_COUNT = 4;

    static uint32_t GetPixel(int colorData);

    int getBytesPerTile() override;
};