#pragma once

#include "PixelDecodeStrategy.h"

namespace OpenUltima {
	class CGALinearDecodeStrategy :
		public PixelDecodeStrategy
	{
	public:
        CGALinearDecodeStrategy(int tileWidth, int tileHeight) : PixelDecodeStrategy(tileWidth, tileHeight) {}

	    vector<uint32_t> GetPixels(vector<uint8_t> bytes) override;
	private:
		static uint32_t GetPixel(int colorData);

		int getBytesPerTile() override;
	};
}

