#pragma once

#include <memory>
#include <utility>
#include <SDL.h>
#include "GameContext.h"

using namespace std;

class Screen {
public:
    static constexpr int WIDTH = 304;
    static constexpr int HEIGHT = 144;

    explicit Screen(shared_ptr<GameContext> gameContext) : _gameContext(std::move(gameContext)) {}

    virtual void update(float elapsed) = 0;

    virtual void draw(SDL_Renderer *renderer) = 0;

    virtual void handle(const SDL_Event &e) {}

protected:
    shared_ptr<GameContext> _gameContext;

    static void clearScreen(SDL_Renderer *renderer);
};

