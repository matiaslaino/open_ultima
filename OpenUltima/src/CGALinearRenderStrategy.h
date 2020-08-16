#pragma once

#include "TileRenderStrategy.h"

namespace OpenUltima {
	class LinearCGARenderStrategy :
		public TileRenderStrategy
	{
	public:
		vector<uint32_t> GetPixels(vector<uint8_t> bytes) override;
	private:
		uint32_t GetPixel(int colorData);
	};
}

