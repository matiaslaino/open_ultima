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
    SDL_RenderDrawLine(renderer, 0, 159, 482 / 2, 159);
    SDL_RenderDrawLine(renderer, 482 / 2, 318 / 2, 482 / 2, 398 / 2);

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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_Rect rect = {258 / 2, 304 / 2, 140 / 2, 16 / 2};
    SDL_RenderFillRect(renderer, &rect);

    rect = {242 / 2, 0, 188 / 2, 16 / 2};
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // upper left triangle thingy
    SDL_RenderDrawLine(renderer, 120, 0, 121, 0);
    SDL_RenderDrawLine(renderer, 122, 1, 123, 1);
    SDL_RenderDrawLine(renderer, 124, 2, 125, 2);
    SDL_RenderDrawLine(renderer, 126, 3, 127, 3);
    SDL_RenderDrawLine(renderer, 125, 4, 126, 4);
    SDL_RenderDrawLine(renderer, 123, 5, 124, 5);
    SDL_RenderDrawLine(renderer, 121, 6, 122, 6);

    // upper left triangle thingy fill
    SDL_SetRenderDrawColor(renderer, 0, 0, 0xAF, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, 120 - 1, 0, 121 - 6, 0);
    SDL_RenderDrawLine(renderer, 122 - 1, 1, 123 - 6, 1);
    SDL_RenderDrawLine(renderer, 124 - 1, 2, 125 - 6, 2);
    SDL_RenderDrawLine(renderer, 126 - 1, 3, 127 - 6, 3);
    SDL_RenderDrawLine(renderer, 125 - 1, 4, 126 - 6, 4);
    SDL_RenderDrawLine(renderer, 123 - 1, 5, 124 - 6, 5);
    SDL_RenderDrawLine(renderer, 121 - 1, 6, 122 - 6, 6);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);


    // upper right triangle thingy
    SDL_RenderDrawLine(renderer, 428 / 2, 0, 428 / 2, 0);
    SDL_RenderDrawLine(renderer, 428 / 2 - 2, 1, 428 / 2 - 1, 1);
    SDL_RenderDrawLine(renderer, 428 / 2 - 4, 2, 428 / 2 - 3, 2);
    SDL_RenderDrawLine(renderer, 428 / 2 - 6, 3, 428 / 2 - 5, 3);
    SDL_RenderDrawLine(renderer, 428 / 2 - 5, 4, 428 / 2 - 4, 4);
    SDL_RenderDrawLine(renderer, 428 / 2 - 3, 5, 428 / 2 - 2, 5);
    SDL_RenderDrawLine(renderer, 428 / 2 - 1, 6, 428 / 2 - 0, 6);

    // upper right triangle thingy fill
    SDL_SetRenderDrawColor(renderer, 0, 0, 0xAF, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, 428 / 2 + 0, 1, 428 / 2 + 7, 1);
    SDL_RenderDrawLine(renderer, 428 / 2 - 2, 2, 428 / 2 + 7, 2);
    SDL_RenderDrawLine(renderer, 428 / 2 - 4, 3, 428 / 2 + 7, 3);
    SDL_RenderDrawLine(renderer, 428 / 2 - 3, 4, 428 / 2 + 7, 4);
    SDL_RenderDrawLine(renderer, 428 / 2 - 1, 5, 428 / 2 + 7, 5);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    constexpr int screenWidth = 304;
    constexpr int screenHeight = 144;
    constexpr int padding = 7;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    // upper
    SDL_RenderDrawLine(renderer, 16 / 2, 14 / 2, 240 / 2, 14 / 2);
    SDL_RenderDrawLine(renderer, 430 / 2, 14 / 2, 622 / 2, 14 / 2);
    // lower
    SDL_RenderDrawLine(renderer, 16 / 2, 304 / 2, 258 / 2, 304 / 2);
    SDL_RenderDrawLine(renderer, 396 / 2, 304 / 2, 622 / 2, 304 / 2);
    // lower left pointy end
    SDL_RenderDrawLine(renderer, 258 / 2, 304 / 2, 258 / 2 + 1, 304 / 2);
    SDL_RenderDrawLine(renderer, 258 / 2 + 2, 304 / 2 + 1, 258 / 2 + 3, 304 / 2 + 1);
    SDL_RenderDrawLine(renderer, 258 / 2 + 4, 304 / 2 + 2, 258 / 2 + 5, 304 / 2 + 2);
    SDL_RenderDrawLine(renderer, 258 / 2 + 6, 304 / 2 + 3, 258 / 2 + 7, 304 / 2 + 3);
    SDL_RenderDrawLine(renderer, 258 / 2 + 5, 304 / 2 + 4, 258 / 2 + 6, 304 / 2 + 4);
    SDL_RenderDrawLine(renderer, 258 / 2 + 3, 304 / 2 + 5, 258 / 2 + 4, 304 / 2 + 5);
    SDL_RenderDrawLine(renderer, 258 / 2 + 1, 304 / 2 + 6, 258 / 2 + 2, 304 / 2 + 6);
    // lower left pointy end fill
    SDL_SetRenderDrawColor(renderer, 0, 0, 0xAF, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, 258 / 2, 304 / 2 + 1, 258 / 2 + 1, 304 / 2 + 1);
    SDL_RenderDrawLine(renderer, 258 / 2, 304 / 2 + 2, 258 / 2 + 3, 304 / 2 + 2);
    SDL_RenderDrawLine(renderer, 258 / 2, 304 / 2 + 3, 258 / 2 + 5, 304 / 2 + 3);
    SDL_RenderDrawLine(renderer, 258 / 2, 304 / 2 + 4, 258 / 2 + 4, 304 / 2 + 4);
    SDL_RenderDrawLine(renderer, 258 / 2, 304 / 2 + 5, 258 / 2 + 2, 304 / 2 + 5);
    SDL_RenderDrawLine(renderer, 258 / 2, 304 / 2 + 6, 258 / 2 + 0, 304 / 2 + 6);


    // lower right pointy end
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderDrawLine(renderer, 396 / 2, 304 / 2, 396 / 2, 304 / 2);
    SDL_RenderDrawLine(renderer, 396 / 2 - 2, 304 / 2 + 1, 396 / 2 - 1, 304 / 2 + 1);
    SDL_RenderDrawLine(renderer, 396 / 2 - 4, 304 / 2 + 2, 396 / 2 - 3, 304 / 2 + 2);
    SDL_RenderDrawLine(renderer, 396 / 2 - 6, 304 / 2 + 3, 396 / 2 - 5, 304 / 2 + 3);
    SDL_RenderDrawLine(renderer, 396 / 2 - 5, 304 / 2 + 4, 396 / 2 - 4, 304 / 2 + 4);
    SDL_RenderDrawLine(renderer, 396 / 2 - 3, 304 / 2 + 5, 396 / 2 - 2, 304 / 2 + 5);
    SDL_RenderDrawLine(renderer, 396 / 2 - 1, 304 / 2 + 6, 396 / 2 - 0, 304 / 2 + 6);
    // lower right pointy end fill
    SDL_SetRenderDrawColor(renderer, 0, 0, 0xAF, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, 396 / 2 - 0, 304 / 2 + 1, 396 / 2, 304 / 2 + 1);
    SDL_RenderDrawLine(renderer, 396 / 2 - 2, 304 / 2 + 2, 396 / 2, 304 / 2 + 2);
    SDL_RenderDrawLine(renderer, 396 / 2 - 4, 304 / 2 + 3, 396 / 2, 304 / 2 + 3);
    SDL_RenderDrawLine(renderer, 396 / 2 - 3, 304 / 2 + 4, 396 / 2, 304 / 2 + 4);
    SDL_RenderDrawLine(renderer, 396 / 2 - 1, 304 / 2 + 5, 396 / 2, 304 / 2 + 5);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // left
    SDL_RenderDrawLine(renderer, padding, padding + 1, padding, padding + screenHeight);

    // right
    SDL_RenderDrawLine(renderer, padding + screenWidth + 1, padding + 1, padding + screenWidth + 1,
                       padding + screenHeight);

    // actions box
    SDL_RenderDrawLine(renderer, 0, 318 / 2, 258 / 2, 318 / 2);
    SDL_RenderDrawLine(renderer, 398 / 2, 318 / 2, 482 / 2, 318 / 2);
    SDL_RenderDrawLine(renderer, 482 / 2, 318 / 2, 482 / 2, 398 / 2);

    // stats box
    SDL_RenderDrawLine(renderer, 246, 159, 246, 199);
    SDL_RenderDrawLine(renderer, 246, 159, 319, 159);
}
