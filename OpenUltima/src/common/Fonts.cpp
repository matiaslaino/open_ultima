#include "Fonts.h"

TTF_Font* Fonts::_standard = nullptr;

void Fonts::init(SDL_Renderer* renderer) {
	_standard = TTF_OpenFont("./resources/PC_Senior_Regular.ttf", 8);
}