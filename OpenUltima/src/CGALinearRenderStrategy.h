#pragma once

#include "TileRenderStrategy.h"

namespace OpenUltima {
	class CGALinearRenderStrategy :
		public TileRenderStrategy
	{
	public:
		void Draw(SDL_Renderer* renderer, SDL_Rect box, vector<uint8_t> bytes) override;

	private:
		void DrawPixel(SDL_Renderer* renderer, int x, int y, int colorData);
	};
}

