#pragma once
#include "TileRenderStrategy.h"

namespace OpenUltima {

	class EGARowPlanarRenderStrategy :
		public TileRenderStrategy
	{
	public:
		vector<uint32_t> GetPixels(vector<uint8_t> bytes) override;
	private:
		static constexpr int PLANES_COUNT = 4;

		uint32_t GetPixel(int colorData);
	};
};