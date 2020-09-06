#pragma once

#include "../Screen.h"

#include <utility>
#include "Town.h"
#include "TownManager.h"

class TownScreen : public Screen {
public:
    explicit TownScreen(const shared_ptr<GameContext> &gameContext, shared_ptr<TownManager> townManager)
            : Screen(gameContext), _townManager(std::move(townManager)) {}

    void update(float elapsed) override;

    void draw(SDL_Renderer *renderer) override;

    void handle(const SDL_Event &e) override;

    void refresh();

private:
    shared_ptr<Town> _town = nullptr;
    shared_ptr<TownManager> _townManager;
};