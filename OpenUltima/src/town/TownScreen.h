#pragma once

#include "../Screen.h"

#include <utility>
#include "Town.h"
#include "TownManager.h"

class TownScreen : public Screen {
public:
    TownScreen(const shared_ptr<GameContext> &gameContext, SDL_Renderer *renderer);

    void update(float elapsed) override;

    void draw(SDL_Renderer *renderer) override;

    void handle(const SDL_Event &e) override;

    void refresh();

private:
    static constexpr int PLAYER_INITIAL_TOWN_POSITION_X = 19;
    static constexpr int PLAYER_INITIAL_TOWN_POSITION_Y = 17;
    static constexpr int PLAYER_INITIAL_CASTLE_POSITION_X = 0;
    static constexpr int PLAYER_INITIAL_CASTLE_POSITION_Y = 7;

    shared_ptr<TownManager> _townManager;
    shared_ptr<TownSpriteTypeLoader> _townSpriteTypeLoader;

    shared_ptr<Town> _currentTown = nullptr;
    shared_ptr<TownTile> _playerTile;

    void resetPlayerPosition();

    void playerMove(CardinalPoint direction);
};