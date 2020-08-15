#pragma once
#include "TileRenderStrategy.h"

namespace OpenUltima {

	class EGARowPlanarRenderStrategy :
		public TileRenderStrategy
	{
	public:
		void Draw(SDL_Renderer* renderer, SDL_Rect box, vector<uint8_t> bytes) override;

	private:
		static constexpr int PLANES_COUNT = 4;

		void DrawPixel(SDL_Renderer* renderer, int x, int y, int colorData);
	};
};