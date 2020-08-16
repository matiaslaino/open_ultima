#pragma once
#include <SDL.h>
#include <vector>

using namespace std;

namespace OpenUltima {
	class TileRenderStrategy
	{
	public:
		virtual vector<uint32_t> GetPixels(vector<uint8_t> bytes) = 0;
	};
}

