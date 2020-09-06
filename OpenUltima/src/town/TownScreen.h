#pragma once

#include "../Screen.h"
#include "Town.h"

class TownScreen : public Screen {
public:
    explicit TownScreen(const shared_ptr<GameContext> &gameContext) : Screen(gameContext) {}

    void update(float elapsed) override;

    void draw(SDL_Renderer *renderer) override;

    void handle(const SDL_Event &e) override;

    void setTown(shared_ptr<Town> town);

private:
    shared_ptr<Town> _town = nullptr;
};