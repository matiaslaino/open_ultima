#include "DungeonScreen.h"
#include "../CommandDisplay.h"
#include "Door.h"
#include "../common/ShapeUtils.h"

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
    ShapeUtils::drawDungeonBorders(renderer);

    // TODO: not too happy with the viewport thingy
    SDL_Rect defaultViewport = {MAIN_VIEWPORT_PADDING, MAIN_VIEWPORT_PADDING, WIDTH, HEIGHT};
    SDL_RenderSetViewport(renderer, &defaultViewport);

    clearScreen(renderer);

    // the _drawEnabled flag controls drawing to the screen.
    // this is to have a flicker effect similar to the original game so that the player sees a small delay in the drawing after an action.
    if (!_drawEnabled) return;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    constexpr int DRAWING_PADDING = 8;

    if (_vision[0].feature == DungeonFeature::Door) {
        // We're standing inside a doorway, this screws up everything.
        // If looking through the doorway, we only care about the following two spaces: the next corridor space, and the wall after it.
        // Remember this whole dungeon design depends on everything being laid down in straight corridors, it's a mess!
        if (_vision.size() == 3) {
            // We're looking through the doorway.
            // Draw the arch and what's after it.

            // Draw arch first
            // Top
            SDL_RenderDrawLine(renderer, 16, 8, 16 + 272, 8);
            // Bottom left
            SDL_RenderDrawLine(renderer, 16, 135, 16 + 65, 135);
            SDL_RenderDrawLine(renderer, 80, 135, 80, 135 - 99);

            SDL_RenderDrawLine(renderer, 80, 36, 80 + 144, 36);

            SDL_RenderDrawLine(renderer, 80 + 144, 36, 80 + 144, 36 + 99);
            SDL_RenderDrawLine(renderer, 80 + 144, 36 + 99, 80 + 144 + 65, 36 + 99);

            // Draw what's after the arch, it should only be either a straight wall, a hidden door (looks like a wall) or another door.
            SDL_RenderDrawLine(renderer, 16 + 65, 54, 16 + 65 + 143, 54);
            SDL_RenderDrawLine(renderer, 16 + 65, 89, 16 + 65 + 143, 89);

            // If there is a door at the other side, draw it
            if (_vision[2].feature == DungeonFeature::Door) {
                SDL_RenderDrawLine(renderer, 134, 89, 134, 89 - 26);
                SDL_RenderDrawLine(renderer, 134, 89 - 26, 134 + 35, 89 - 26);
                SDL_RenderDrawLine(renderer, 134 + 35, 89 - 26, 134 + 35, 89 - 26 + 26);
            }
        } else {
            // We're inside a doorway, but facing the side walls, nothing to see but a wall
            SDL_RenderDrawLine(renderer, 16, 8, 16 + 272, 8);
            SDL_RenderDrawLine(renderer, 16, 135, 80 + 144 + 65, 135);
        }
    } else {
        // First draw all the walls
        if (_vision.size() == 2) {
            // 2 tiles of vision means the tile we are in right now, and the next tile is a wall/door (if it wasn't a wall, we'd be able to see past it)
            // x1 --> left point, x2 --> right point, y1 --> upper point, y2 --> lower point
            constexpr int oppositeWallX1 = 80;
            constexpr int oppositeWallY1 = 36;
            constexpr int oppositeWallX2 = oppositeWallX1 + 144 - 1;
            constexpr int oppositeWallY2 = oppositeWallY1 + 72 - 1;

            // draw the upper and lower lines of the opposite wall.
            SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY1, oppositeWallX2, oppositeWallY1);
            SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY2, oppositeWallX2, oppositeWallY2);

            if (isWalledFeature(_vision[0].left)) {
                SDL_RenderDrawLine(renderer, UPPER_LEFT_X, UPPER_LEFT_Y, oppositeWallX1, oppositeWallY1);
                SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY1, oppositeWallX1, oppositeWallY2);
                SDL_RenderDrawLine(renderer, LOWER_LEFT_X, LOWER_LEFT_Y, oppositeWallX1, oppositeWallY2);
            } else {
                SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY1, DRAWING_PADDING, oppositeWallY1);
                SDL_RenderDrawLine(renderer, oppositeWallX1, oppositeWallY2, DRAWING_PADDING, oppositeWallY2);
            }

            if (isWalledFeature(_vision[0].right)) {
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
    }

    // level position x: 136

    // draw sprites
    int distance = 0;
    for (const auto &tile : _vision) {

        if (tile.right == DungeonFeature::Door) {
            Door::draw(renderer, distance, Direction::Right);
        }

        if (tile.left == DungeonFeature::Door) {
            Door::draw(renderer, distance, Direction::Left);
        }

        if (tile.feature == DungeonFeature::Door) {
            if (distance != 0) {
                Door::drawFrontFacing(renderer, distance);
            }
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
            default:
                return;
        }

        _vision = _dungeon->getVisible(player->getDungeonLevel(), player->getDungeonX(), player->getDungeonY(),
                                       player->getDungeonOrientation());
        _drawEnabled = false;
    }
}

void DungeonScreen::moveForward() {
    auto player = _gameContext->getPlayer();
    if (_vision[1].feature == DungeonFeature::Wall) return;

    // If we arrive to this point, we're either inside a door, or in a hallway and can move forward.
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