#include "ShapeUtils.h"

shared_ptr<LTexture> ShapeUtils::arrow(SDL_Renderer *renderer, Direction direction) {
    SDL_Texture *sdlTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 8, 8);
    shared_ptr<LTexture> texture = make_shared<LTexture>(sdlTexture, 8, 8);
    SDL_Rect target = {0, 0, 8, 8};

    uint32_t white = 0xFFFFFF00;
    uint32_t black = 0;
    uint32_t blue = 0x0000AF00;

    if (direction == Direction::Right) {
        uint32_t pixels[64] = {
                white, white, black, black, black, black, black, black,
                blue, blue, white, white, black, black, black, black,
                blue, blue, blue, blue, white, white, black, black,
                blue, blue, blue, blue, blue, blue, white, white,
                blue, blue, blue, blue, blue, white, white, black,
                blue, blue, blue, white, white, black, black, black,
                blue, white, white, black, black, black, black, black,
                white, black, black, black, black, black, black, black,
        };
        SDL_UpdateTexture(sdlTexture, &target, &pixels, 8 * sizeof(uint32_t));
    } else {
        uint32_t pixels[64] = {
                black, black, black, black, black, black, white, white,
                black, black, black, black, white, white, blue, blue,
                black, black, white, white, blue, blue, blue, blue,
                white, white, blue, blue, blue, blue, blue, blue,
                black, white, white, blue, blue, blue, blue, blue,
                black, black, black, white, white, blue, blue, blue,
                black, black, black, black, black, white, white, blue,
                black, black, black, black, black, black, black, white,
        };
        SDL_UpdateTexture(sdlTexture, &target, &pixels, 8 * sizeof(uint32_t));
    }

    return texture;
}

void ShapeUtils::drawFullBorders(SDL_Renderer *renderer) {
    constexpr int screenWidth = 304;
    constexpr int screenHeight = 144;
    constexpr int padding = 7;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    // upper
    SDL_RenderDrawLine(renderer, padding + 1, padding, padding + screenWidth, padding);
    // lower
    SDL_RenderDrawLine(renderer, padding + 1, padding + screenHeight + 1,
                       padding + screenWidth, padding + screenHeight + 1);

    // left
    SDL_RenderDrawLine(renderer, padding, padding + 1, padding, padding + screenHeight);

    // right
    SDL_RenderDrawLine(renderer, padding + screenWidth + 1, padding + 1, padding + screenWidth + 1,
                       padding + screenHeight);

    // actions box
    SDL_RenderDrawLine(renderer, 0, 159, 242, 159);
    SDL_RenderDrawLine(renderer, 242, 159, 242, 199);

    // stats box
    SDL_RenderDrawLine(renderer, 246, 159, 246, 199);
    SDL_RenderDrawLine(renderer, 246, 159, 319, 159);
}

void ShapeUtils::drawRoundedCorners(SDL_Renderer *renderer) {
// upper left triangle
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderDrawLine(renderer, 0, 0, 5, 0);
    SDL_RenderDrawLine(renderer, 0, 1, 3, 1);
    SDL_RenderDrawLine(renderer, 0, 2, 2, 2);
    SDL_RenderDrawLine(renderer, 0, 3, 1, 3);
    SDL_RenderDrawLine(renderer, 0, 4, 0, 4);
    SDL_RenderDrawLine(renderer, 0, 5, 0, 5);

    // upper right triangle
    SDL_RenderDrawLine(renderer, 319, 0, 319 - 5, 0);
    SDL_RenderDrawLine(renderer, 319, 1, 319 - 3, 1);
    SDL_RenderDrawLine(renderer, 319, 2, 319 - 2, 2);
    SDL_RenderDrawLine(renderer, 319, 3, 319 - 1, 3);
    SDL_RenderDrawLine(renderer, 319, 4, 319, 4);
    SDL_RenderDrawLine(renderer, 319, 5, 319, 5);
}

void ShapeUtils::drawDungeonBorders(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderDrawLine(renderer, 120, 0, 121, 0);
    SDL_RenderDrawLine(renderer, 122, 1, 123, 1);
    SDL_RenderDrawLine(renderer, 124, 2, 125, 2);
    SDL_RenderDrawLine(renderer, 126, 3, 127, 3);
    SDL_RenderDrawLine(renderer, 125, 4, 126, 4);
    SDL_RenderDrawLine(renderer, 123, 5, 124, 5);
    SDL_RenderDrawLine(renderer, 121, 6, 122, 6);
}
