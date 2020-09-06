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
    if (e.type == SDL_KEYDOWN) {
        auto pressedKey = e.key.keysym.sym;

        switch (pressedKey) {
            case SDLK_e:
                _gameContext->setScreen(ScreenType::Overworld);
                break;
        }
    }
}

void TownScreen::refresh() {
    int x = _gameContext->getPlayer()->getOverworldX();
    int y = _gameContext->getPlayer()->getOverworldY();

    if (_gameContext->isInCastle()) {
        _town = _townManager->getCastle(x, y);
    } else {
        _town = _townManager->getTown(x, y);
    }
}