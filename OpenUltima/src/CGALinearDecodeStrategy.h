#pragma once

#include "PixelDecodeStrategy.h"

namespace OpenUltima {
	class CGALinearDecodeStrategy :
		public PixelDecodeStrategy
	{
	public:
		vector<uint32_t> GetPixels(vector<uint8_t> bytes) override;
	private:
		uint32_t GetPixel(int colorData);
	};
}

