#include "TownScreen.h"

#include <utility>

void TownScreen::update(float elapsed) {

}

void TownScreen::draw(SDL_Renderer *renderer) {
    clearScreen(renderer);

    auto tiles = _town->getTiles();
    constexpr SDL_Rect camera = {0, 0, Screen::WIDTH, Screen::HEIGHT};
    for (const auto &tile: tiles) {
        tile->draw(renderer, camera);
    }
}

void TownScreen::handle(const SDL_Event &e) {
    Screen::handle(e);
}

void TownScreen::setTown(shared_ptr<Town> town) {
    _town = std::move(town);
}
