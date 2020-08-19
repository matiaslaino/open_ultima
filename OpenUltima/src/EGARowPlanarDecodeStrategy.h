#pragma once
#include "PixelDecodeStrategy.h"

namespace OpenUltima {

	class EGARowPlanarDecodeStrategy :
		public PixelDecodeStrategy
	{
	public:
		vector<uint32_t> GetPixels(vector<uint8_t> bytes) override;
	private:
		static constexpr int PLANES_COUNT = 4;

		uint32_t GetPixel(int colorData);

		virtual const int getBytesPerTile() override;
	};
};