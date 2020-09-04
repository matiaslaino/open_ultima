#include "CGALinearDecodeStrategy.h"
#include <SDL.h>
#include <vector>

using namespace std;
using namespace OpenUltima;

uint32_t CGALinearDecodeStrategy::GetPixel(int colorData) {
    if (colorData == 0b11) {
        // white
        return 0xFFFFFF00;
    }

    if (colorData == 0b01) {
        // light cyan
        return 0x55FFFF00;
    }

    if (colorData == 0b10) {
        // light magenta
        return 0xFF55FF00;
    }

    // black
    return 0x00000000;
}

int OpenUltima::CGALinearDecodeStrategy::getBytesPerTile() {
    return 64;
}

vector<uint32_t> OpenUltima::CGALinearDecodeStrategy::GetPixels(vector<uint8_t> bytes) {
    // In CGA Linear, each byte represents 4 pixel, meaning 2 bits specify the color of a single pixel.
    vector<uint32_t> pixels;
    int byteIndex = 0;

    for (auto byte : bytes) {
        auto pixel4 = byte & 0b00000011;
        auto pixel3 = (byte & 0b00001100) >> 2;
        auto pixel2 = (byte & 0b00110000) >> 4;
        auto pixel1 = (byte & 0b11000000) >> 6;

        pixels.push_back(GetPixel(pixel1));
        pixels.push_back(GetPixel(pixel2));
        pixels.push_back(GetPixel(pixel3));
        pixels.push_back(GetPixel(pixel4));
    }

    return pixels;
}
