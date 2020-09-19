#include "Ladder.h"
#include <vector>
#include "SDL2_gfxPrimitives.h"

using namespace std;

void Ladder::drawFront(SDL_Renderer *renderer, int distance, bool goingUp) {
    if (goingUp) {
        if (distance == 0) {
            vector<Sint16> pointsX = {
                    164 / 2, 224 / 2, 386 / 2, 444 / 2
            };

            vector<Sint16> pointsY = {
                    22 / 2, 52 / 2, 52 / 2, 22 / 2
            };

            polygonColor(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0xFFFFFFFF);

            SDL_RenderDrawLine(renderer, 264 / 2, 22 / 2, 264 / 2, 262 / 2);
            SDL_RenderDrawLine(renderer, 344 / 2, 22 / 2, 344 / 2, 262 / 2);

            SDL_RenderDrawLine(renderer, 264 / 2, 62 / 2, 344 / 2, 62 / 2);
            SDL_RenderDrawLine(renderer, 264 / 2, 112 / 2, 344 / 2, 112 / 2);
            SDL_RenderDrawLine(renderer, 264 / 2, 172 / 2, 344 / 2, 172 / 2);
            SDL_RenderDrawLine(renderer, 264 / 2, 232 / 2, 344 / 2, 232 / 2);

        } else if (distance == 1) {
            vector<Sint16> pointsX = {
                    234 / 2, 374 / 2, 346 / 2, 262 / 2
            };

            vector<Sint16> pointsY = {
                    88 / 2, 88 / 2, 102 / 2, 102 / 2
            };

            polygonColor(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0xFFFFFFFF);

            SDL_RenderDrawLine(renderer, 284 / 2, 88 / 2, 284 / 2, 208 / 2);
            SDL_RenderDrawLine(renderer, 324 / 2, 88 / 2, 324 / 2, 208 / 2);

            SDL_RenderDrawLine(renderer, 284 / 2, 102 / 2, 324 / 2, 102 / 2);
            SDL_RenderDrawLine(renderer, 284 / 2, 132 / 2, 324 / 2, 132 / 2);
            SDL_RenderDrawLine(renderer, 284 / 2, 162 / 2, 324 / 2, 162 / 2);
            SDL_RenderDrawLine(renderer, 284 / 2, 192 / 2, 324 / 2, 192 / 2);
        } else if (distance == 2) {
            vector<Sint16> pointsX = {
                    268 / 2, 338 / 2, 326 / 2, 282 / 2
            };

            vector<Sint16> pointsY = {
                    116 / 2, 116 / 2, 122 / 2, 122 / 2
            };

            polygonColor(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0xFFFFFFFF);

            SDL_RenderDrawLine(renderer, 294 / 2, 116 / 2, 294 / 2, 176 / 2);
            SDL_RenderDrawLine(renderer, 314 / 2, 116 / 2, 314 / 2, 176 / 2);

            SDL_RenderDrawLine(renderer, 294 / 2, 126 / 2, 314 / 2, 126 / 2);
            SDL_RenderDrawLine(renderer, 294 / 2, 138 / 2, 314 / 2, 138 / 2);
            SDL_RenderDrawLine(renderer, 294 / 2, 152 / 2, 314 / 2, 152 / 2);
            SDL_RenderDrawLine(renderer, 294 / 2, 168 / 2, 314 / 2, 168 / 2);
        } else if (distance == 3) {
            vector<Sint16> pointsX = {
                    286 / 2, 320 / 2, 316 / 2, 292 / 2
            };

            vector<Sint16> pointsY = {
                    130 / 2, 130 / 2, 132 / 2, 132 / 2
            };

            polygonColor(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0xFFFFFFFF);

            SDL_RenderDrawLine(renderer, 298 / 2, 132 / 2, 298 / 2, 160 / 2);
            SDL_RenderDrawLine(renderer, 308 / 2, 132 / 2, 308 / 2, 160 / 2);

            SDL_RenderDrawLine(renderer, 298 / 2, 140 / 2, 308 / 2, 140 / 2);
            SDL_RenderDrawLine(renderer, 298 / 2, 148 / 2, 308 / 2, 148 / 2);
            SDL_RenderDrawLine(renderer, 298 / 2, 156 / 2, 308 / 2, 156 / 2);
        } else if (distance == 4) {
            SDL_RenderDrawLine(renderer, 302 / 2, 146 / 2, 302 / 2, 148 / 2);
            SDL_RenderDrawLine(renderer, 303 / 2, 146 / 2, 303 / 2, 148 / 2);
        }
    } else {
        // I do all these weird substractions everywhere because the down ladder is the upside down version of the up ladder and i was too lazy to get all the coordinates again or calculate them, let the system do it!
        constexpr int middleY = 144 / 2;

        if (distance == 0) {
            vector<Sint16> pointsX = {
                    164 / 2, 224 / 2, 386 / 2, 444 / 2
            };

            vector<Sint16> pointsY = {
                    2 * middleY - 22 / 2, 2 * middleY - 52 / 2, 2 * middleY - 52 / 2, 2 * middleY - 22 / 2
            };

            polygonColor(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0xFFFFFFFF);

            SDL_RenderDrawLine(renderer, 264 / 2, 2 * middleY - 22 / 2, 264 / 2, 2 * middleY - 262 / 2);
            SDL_RenderDrawLine(renderer, 344 / 2, 2 * middleY - 22 / 2, 344 / 2, 2 * middleY - 262 / 2);

            SDL_RenderDrawLine(renderer, 264 / 2, 2 * middleY - 62 / 2, 344 / 2, 2 * middleY - 62 / 2);
            SDL_RenderDrawLine(renderer, 264 / 2, 2 * middleY - 112 / 2, 344 / 2, 2 * middleY - 112 / 2);
            SDL_RenderDrawLine(renderer, 264 / 2, 2 * middleY - 172 / 2, 344 / 2, 2 * middleY - 172 / 2);
            SDL_RenderDrawLine(renderer, 264 / 2, 2 * middleY - 232 / 2, 344 / 2, 2 * middleY - 232 / 2);

        } else if (distance == 1) {
            vector<Sint16> pointsX = {
                    234 / 2, 374 / 2, 346 / 2, 262 / 2
            };

            vector<Sint16> pointsY = {
                    2 * middleY - 88 / 2, 2 * middleY - 88 / 2, 2 * middleY - 102 / 2, 2 * middleY - 102 / 2
            };

            polygonColor(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0xFFFFFFFF);

            SDL_RenderDrawLine(renderer, 284 / 2, 2 * middleY - 88 / 2, 284 / 2, 2 * middleY - 208 / 2);
            SDL_RenderDrawLine(renderer, 324 / 2, 2 * middleY - 88 / 2, 324 / 2, 2 * middleY - 208 / 2);

            SDL_RenderDrawLine(renderer, 284 / 2, 2 * middleY - 102 / 2, 324 / 2, 2 * middleY - 102 / 2);
            SDL_RenderDrawLine(renderer, 284 / 2, 2 * middleY - 132 / 2, 324 / 2, 2 * middleY - 132 / 2);
            SDL_RenderDrawLine(renderer, 284 / 2, 2 * middleY - 162 / 2, 324 / 2, 2 * middleY - 162 / 2);
            SDL_RenderDrawLine(renderer, 284 / 2, 2 * middleY - 192 / 2, 324 / 2, 2 * middleY - 192 / 2);
        } else if (distance == 2) {
            vector<Sint16> pointsX = {
                    268 / 2, 338 / 2, 326 / 2, 282 / 2
            };

            vector<Sint16> pointsY = {
                    2 * middleY - 116 / 2, 2 * middleY - 116 / 2, 2 * middleY - 122 / 2, 2 * middleY - 122 / 2
            };

            polygonColor(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0xFFFFFFFF);

            SDL_RenderDrawLine(renderer, 294 / 2, 2 * middleY - 116 / 2, 294 / 2, 2 * middleY - 176 / 2);
            SDL_RenderDrawLine(renderer, 314 / 2, 2 * middleY - 116 / 2, 314 / 2, 2 * middleY - 176 / 2);

            SDL_RenderDrawLine(renderer, 294 / 2, 2 * middleY - 126 / 2, 314 / 2, 2 * middleY - 126 / 2);
            SDL_RenderDrawLine(renderer, 294 / 2, 2 * middleY - 138 / 2, 314 / 2, 2 * middleY - 138 / 2);
            SDL_RenderDrawLine(renderer, 294 / 2, 2 * middleY - 152 / 2, 314 / 2, 2 * middleY - 152 / 2);
            SDL_RenderDrawLine(renderer, 294 / 2, 2 * middleY - 168 / 2, 314 / 2, 2 * middleY - 168 / 2);
        } else if (distance == 3) {
            vector<Sint16> pointsX = {
                    286 / 2, 320 / 2, 316 / 2, 292 / 2
            };

            vector<Sint16> pointsY = {
                    2 * middleY - 130 / 2, 2 * middleY - 130 / 2, 2 * middleY - 132 / 2, 2 * middleY - 132 / 2
            };

            polygonColor(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0xFFFFFFFF);

            SDL_RenderDrawLine(renderer, 298 / 2, 2 * middleY - 132 / 2, 298 / 2, 2 * middleY - 160 / 2);
            SDL_RenderDrawLine(renderer, 308 / 2, 2 * middleY - 132 / 2, 308 / 2, 2 * middleY - 160 / 2);

            SDL_RenderDrawLine(renderer, 298 / 2, 2 * middleY - 140 / 2, 308 / 2, 2 * middleY - 140 / 2);
            SDL_RenderDrawLine(renderer, 298 / 2, 2 * middleY - 148 / 2, 308 / 2, 2 * middleY - 148 / 2);
            SDL_RenderDrawLine(renderer, 298 / 2, 2 * middleY - 156 / 2, 308 / 2, 2 * middleY - 156 / 2);
        } else if (distance == 4) {
            SDL_RenderDrawLine(renderer, 302 / 2, 2 * middleY - 146 / 2, 302 / 2, 2 * middleY - 148 / 2);
            SDL_RenderDrawLine(renderer, 303 / 2, 2 * middleY - 146 / 2, 303 / 2, 2 * middleY - 148 / 2);
        }
    }
}

void Ladder::drawFromSide(SDL_Renderer *renderer, int distance, bool goingUp) {
    if (!goingUp) {
        if (distance == 0) {
            // upper straight line
            SDL_RenderDrawLine(renderer, 224 / 2, 232 / 2, 386 / 2, 232 / 2);
            // left
            SDL_RenderDrawLine(renderer, 164 / 2, 262 / 2, 224 / 2, 232 / 2);
            // lower straight line
            SDL_RenderDrawLine(renderer, 164 / 2, 262 / 2, 444 / 2, 262 / 2);
            // right
            SDL_RenderDrawLine(renderer, 444 / 2, 262 / 2, 386 / 2, 232 / 2);
            // vertical
            SDL_RenderDrawLine(renderer, 304 / 2, 22 / 2, 304 / 2, 262 / 2);
        } else if (distance == 1) {
            // upper straight line
            SDL_RenderDrawLine(renderer, 234 / 2, 208 / 2, 374 / 2, 208 / 2);
            // left
            SDL_RenderDrawLine(renderer, 234 / 2, 208 / 2, 264 / 2, 192 / 2);
            // lower straight line
            SDL_RenderDrawLine(renderer, 264 / 2, 192 / 2, 344 / 2, 192 / 2);
            // right
            SDL_RenderDrawLine(renderer, 374 / 2, 208 / 2, 344 / 2, 192 / 2);
            // vertical
            SDL_RenderDrawLine(renderer, 304 / 2, 208 / 2, 304 / 2, 88 / 2);
        }
    } else {
        constexpr int middleY = 144 / 2;
        if (distance == 0) {
            // upper straight line
            SDL_RenderDrawLine(renderer, 224 / 2, 2 * middleY - 232 / 2, 386 / 2, 2 * middleY - 232 / 2);
            // left
            SDL_RenderDrawLine(renderer, 164 / 2, 2 * middleY - 262 / 2, 224 / 2, 2 * middleY - 232 / 2);
            // lower straight line
            SDL_RenderDrawLine(renderer, 164 / 2, 2 * middleY - 262 / 2, 444 / 2, 2 * middleY - 262 / 2);
            // right
            SDL_RenderDrawLine(renderer, 444 / 2, 2 * middleY - 262 / 2, 386 / 2, 2 * middleY - 232 / 2);
            // vertical
            SDL_RenderDrawLine(renderer, 304 / 2, 2 * middleY - 22 / 2, 304 / 2, 2 * middleY - 262 / 2);
        } else if (distance == 1) {
            // upper straight line
            SDL_RenderDrawLine(renderer, 234 / 2, 2 * middleY - 208 / 2, 374 / 2, 2 * middleY - 208 / 2);
            // left
            SDL_RenderDrawLine(renderer, 234 / 2, 2 * middleY - 208 / 2, 264 / 2, 2 * middleY - 192 / 2);
            // lower straight line
            SDL_RenderDrawLine(renderer, 264 / 2, 2 * middleY - 192 / 2, 344 / 2, 2 * middleY - 192 / 2);
            // right
            SDL_RenderDrawLine(renderer, 374 / 2, 2 * middleY - 208 / 2, 344 / 2, 2 * middleY - 192 / 2);
            // vertical
            SDL_RenderDrawLine(renderer, 304 / 2, 2 * middleY - 208 / 2, 304 / 2, 2 * middleY - 88 / 2);
        }
    }
}
