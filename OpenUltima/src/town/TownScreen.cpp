#include "TownScreen.h"
#include "../common/graphics/EGARowPlanarDecodeStrategy.h"
#include "../CommandDisplay.h"

TownScreen::TownScreen(const shared_ptr<GameContext> &gameContext, SDL_Renderer *renderer)
        : Screen(gameContext) {
    _townSpriteTypeLoader = make_shared<TownSpriteTypeLoader>();
    _townSpriteTypeLoader->init("F:\\GOGLibrary\\Ultima 1\\EGATOWN.BIN",
                                make_unique<EGARowPlanarDecodeStrategy>(8, 8).get(),
                                renderer);
    _townManager = make_shared<TownManager>();
    _townManager->init(_townSpriteTypeLoader, "F:\\GOGLibrary\\Ultima 1\\TCD.BIN");

    auto playerSpriteType = _townSpriteTypeLoader->getSpriteType(TownSpriteType::SpriteType::PERSON_PLAYER);
    _playerTile = make_shared<TownTile>(PLAYER_INITIAL_TOWN_POSITION_X, PLAYER_INITIAL_TOWN_POSITION_Y,
                                        playerSpriteType);
}

void TownScreen::update(float elapsed) {

}

void TownScreen::handle(const SDL_Event &e) {
    if (e.type == SDL_KEYDOWN) {
        auto pressedKey = e.key.keysym.sym;

        switch (pressedKey) {
            case SDLK_e:
                _gameContext->setScreen(ScreenType::Overworld);
                break;
            case SDLK_UP:
                playerMove(CardinalPoint::North);
                break;
            case SDLK_DOWN:
                playerMove(CardinalPoint::South);
                break;
            case SDLK_LEFT:
                playerMove(CardinalPoint::West);
                break;
            case SDLK_RIGHT:
                playerMove(CardinalPoint::East);
                break;
            default:
                break;
        }
    }
}

void TownScreen::refresh() {
    int x = _gameContext->getPlayer()->getOverworldX();
    int y = _gameContext->getPlayer()->getOverworldY();

    if (_gameContext->isInCastle()) {
        _currentTown = _townManager->getCastle(x, y);
    } else {
        _currentTown = _townManager->getTown(x, y);
    }

    // reset player starting position on town.
    resetPlayerPosition();
}

void TownScreen::draw(SDL_Renderer *renderer) {
    SDL_Rect defaultViewport = {MAIN_VIEWPORT_PADDING, MAIN_VIEWPORT_PADDING, WIDTH, HEIGHT};
    SDL_RenderSetViewport(renderer, &defaultViewport);

    clearScreen(renderer);

    auto tiles = _currentTown->getTiles();
    constexpr SDL_Rect camera = {0, 0, Screen::WIDTH, Screen::HEIGHT};
    for (const auto &tile: tiles) {
        tile->draw(renderer, camera);
    }

    _playerTile->draw(renderer, camera);
}

void TownScreen::resetPlayerPosition() {
    if (_currentTown->isCastle()) {
        _playerTile->setCoordinates(PLAYER_INITIAL_CASTLE_POSITION_X,
                                    PLAYER_INITIAL_CASTLE_POSITION_Y);
    } else {
        _playerTile->setCoordinates(PLAYER_INITIAL_TOWN_POSITION_X,
                                    PLAYER_INITIAL_TOWN_POSITION_Y);
    }
}

void TownScreen::playerMove(CardinalPoint direction) {
    int nextX = _playerTile->getX();
    int nextY = _playerTile->getY();

    switch (direction) {
        case CardinalPoint::North:
            nextY--;
            break;
        case CardinalPoint::South:
            nextY++;
            break;
        case CardinalPoint::East:
            nextX++;
            break;
        case CardinalPoint::West:
            nextX--;
            break;
    }

    bool blocked = nextX < 0 ||
                   nextX >= Town::WIDTH ||
                   nextY < 0 ||
                   nextY >= Town::HEIGHT;

    if (!blocked) {
        auto nextTile = _currentTown->getTile(nextX, nextY);
        TownSpriteType::SpriteType spriteType = nextTile->getType();
        blocked = spriteType != TownSpriteType::SpriteType::FLOOR && spriteType != TownSpriteType::SpriteType::NONE;
    }

    if (blocked) {
        CommandDisplay::writeLn("Blocked!", true);
        return;
    }

    _playerTile->setCoordinates(nextX, nextY);
}
