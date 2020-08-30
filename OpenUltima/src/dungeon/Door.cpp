#include "Door.h"

void Door::draw(SDL_Renderer* renderer, int distance, Direction direction)
{
	int halfScreenOffset = 152;

	int x1, x2;

	if (distance == 4) {
		if (direction == Direction::Right) {
			x1 = halfScreenOffset + 4;
			x2 = x1 + 2;
		}
		else {
			x1 = halfScreenOffset - 4;
			x2 = x1 - 2;
		}

		SDL_RenderDrawLine(renderer, x1, 73, x1, 72);
		SDL_RenderDrawLine(renderer, x1, 72, x2, 71);
		SDL_RenderDrawLine(renderer, x2, 71, x2, 74);
	}
	else if (distance == 3) {
		if (direction == Direction::Right) {
			x1 = halfScreenOffset + 11;
			x2 = x1 + 3;
		}
		else {
			x1 = halfScreenOffset - 11;
			x2 = x1 - 3;
		}

		SDL_RenderDrawLine(renderer, x1, 76, x1, 70);
		SDL_RenderDrawLine(renderer, x1, 70, x2, 69);
		SDL_RenderDrawLine(renderer, x2, 69, x2, 78);
	}
	else if (distance == 2) {
		if (direction == Direction::Right) {
			x1 = halfScreenOffset + 23;
			x2 = x1 + 7;
		}
		else {
			x1 = halfScreenOffset - 23;
			x2 = x1 - 7;
		}

		SDL_RenderDrawLine(renderer, x1, 82, x1, 66);
		SDL_RenderDrawLine(renderer, x1, 66, x2, 63);
		SDL_RenderDrawLine(renderer, x2, 63, x2, 86);
	}
	else if (distance == 1) {
		if (direction == Direction::Right) {
			x1 = halfScreenOffset + 47;
			x2 = x1 + 17;
		}
		else {
			x1 = halfScreenOffset - 47;
			x2 = x1 - 17;
		}

		SDL_RenderDrawLine(renderer, x1, 94, x1, 56);
		SDL_RenderDrawLine(renderer, x1, 56, x2, 49);
		SDL_RenderDrawLine(renderer, x2, 49, x2, 103);
	}
	else if (distance == 0) {
		if (direction == Direction::Right) {
			x1 = halfScreenOffset + 95;
			x2 = x1 + 31;
		}
		else {
			x1 = halfScreenOffset - 95;
			x2 = x1 - 31;
		}

		SDL_RenderDrawLine(renderer, x1, 118, x1, 43);
		SDL_RenderDrawLine(renderer, x1, 43, x2, 29);
		SDL_RenderDrawLine(renderer, x2, 29, x2, 134);
	}
}
