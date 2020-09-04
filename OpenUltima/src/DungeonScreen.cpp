#include "DungeonScreen.h"
#include "CommandDisplay.h"
#include "dungeon/Door.h"

void DungeonScreen::update(float elapsed) {
    if (!_drawEnabled) {
        _drawCounter += elapsed;
        if (_drawCounter >= 100) {
            _drawEnabled = true;
            _drawCounter = 0;
        }
    }
}

void DungeonScreen::draw(SDL_Renderer *renderer) {
    clearScreen(renderer);

    // the _drawEnabled flag controls drawing to the screen.
    // this is to have a flicker effect similar to the original game so that the player sees a small delay in the drawing after an action.
    if (!_drawEnabled) return;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    constexpr int DRAWING_PADDING = 8;

    // First draw all the walls
    if (_vision.size() == 2) {
        // 2 tiles of vision means the tile we are in right now, and the next tile is a wall (if it wasn't a wall, we'd be able to see past it)
        // x1 --> left point, x2 --> right point, y1 --> upper point, y2 --> lower point
        constexpr int oppositeWallX1 = 80;
        constexpr int oppositeWallY1 = 36;
        constexpr int oppositeWallX2 = oppositeWallX1 + 144 - 1;
        constexpr int oppositeWallY2 = oppositeWallY1 + 72 - 1;

        // draw the upper and lower lines of the opposite wall.
        SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY1, oppositeWallX2, oppositeWallY1);
        SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY2, oppositeWallX2, oppositeWallY2);

        if (isWalledFeature(_vision[0].left->feature)) {
            SDL_RenderDrawLine(renderer, UPPER_LEFT_X, UPPER_LEFT_Y, oppositeWallX1, oppositeWallY1);
            SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY1, oppositeWallX1, oppositeWallY2);
            SDL_RenderDrawLine(renderer, LOWER_LEFT_X, LOWER_LEFT_Y, oppositeWallX1, oppositeWallY2);
        } else {
            SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY1, DRAWING_PADDING, oppositeWallY1);
            SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY2, DRAWING_PADDING, oppositeWallY2);
        }

        if (isWalledFeature(_vision[0].right->feature)) {
            SDL_RenderDrawLine(renderer, UPPER_RIGHT_X, UPPER_RIGHT_Y, oppositeWallX2, oppositeWallY1);
            SDL_RenderDrawLine(renderer, oppositeWallX2, oppositeWallY1, oppositeWallX2, oppositeWallY2);
            SDL_RenderDrawLine(renderer, LOWER_RIGHT_X, LOWER_RIGHT_Y, oppositeWallX2, oppositeWallY2);
        } else {
            SDL_RenderDrawLine(renderer, oppositeWallX2, oppositeWallY1, WIDTH - DRAWING_PADDING, oppositeWallY1);
            SDL_RenderDrawLine(renderer, oppositeWallX2, oppositeWallY2, WIDTH - DRAWING_PADDING, oppositeWallY2);
        }
    } else {
        drawLeftWalls(renderer);
        drawRightWalls(renderer);

        // This is the vision "horizon"
        SDL_RenderDrawLine(renderer, 149, 72, 155, 72);
        SDL_RenderDrawLine(renderer, 149, 73, 155, 73);

        // If there is something at 5 spots away, it could either mean it's a wall, or is just the limit of visibility.
        if (_vision.size() == 5 && isWalledFeature(_vision[4].feature)) {
            SDL_Rect oppositeWallRect = {143, 69, 18, 7};

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderFillRect(renderer, &oppositeWallRect);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderDrawRect(renderer, &oppositeWallRect);
        } else if (_vision.size() == 4) {
            SDL_Rect oppositeWallRect = {134, 64, 36, 17};

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderFillRect(renderer, &oppositeWallRect);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderDrawRect(renderer, &oppositeWallRect);
        } else if (_vision.size() == 3) {
            SDL_Rect oppositeWallRect = {116, 55, 72, 35};

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderFillRect(renderer, &oppositeWallRect);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderDrawRect(renderer, &oppositeWallRect);
        }
    }

    // draw sprites
    int distance = 0;
    for (const auto& tile : _vision) {
        if (tile.right->feature == DungeonFeature::Door) {
            Door::draw(renderer, distance, Direction::Right);
        }

        if (tile.left->feature == DungeonFeature::Door) {
            Door::draw(renderer, distance, Direction::Left);
        }

        if (tile.feature == DungeonFeature::Door) {
            Door::drawFrontFacing(renderer);
        }

        distance++;
    }
}

void DungeonScreen::handle(const SDL_Event &e) {
    auto player = _gameContext->getPlayer();

    if (e.type == SDL_KEYDOWN) {
        auto pressedKey = e.key.keysym.sym;

        switch (pressedKey) {
            case SDLK_UP:
                moveForward();
                break;
            case SDLK_DOWN:
                player->dungeonTurn(Direction::Right);
                player->dungeonTurn(Direction::Right);
                CommandDisplay::write("Turn around", true);
                break;
            case SDLK_LEFT:
                player->dungeonTurn(Direction::Left);
                CommandDisplay::write("Turn left", true);
                break;
            case SDLK_RIGHT:
                player->dungeonTurn(Direction::Right);
                CommandDisplay::write("Turn right", true);
                break;
        }

        _vision = _dungeon->getVisible(player->getDungeonLevel(), player->getDungeonX(), player->getDungeonY(),
                                       player->getDungeonOrientation());
        _drawEnabled = false;
    }
}

void DungeonScreen::moveForward() {
    auto player = _gameContext->getPlayer();
    if (_vision[1].feature == DungeonFeature::Wall) return;

    player->dungeonMoveForward();
    CommandDisplay::write("Forward", true);
}

void DungeonScreen::drawLeftWalls(SDL_Renderer *renderer) {
    SDL_RenderDrawLine(renderer, 8, 0, 149, 72);
    SDL_RenderDrawLine(renderer, 8, 144, 149, 73);
}

void DungeonScreen::drawRightWalls(SDL_Renderer *renderer) {
    SDL_RenderDrawLine(renderer, 296, 0, 155, 72);
    SDL_RenderDrawLine(renderer, 296, 144, 155, 73);
}
