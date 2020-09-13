#include "GiantRat.h"
#include "SDL2_gfxPrimitives.h"
#include <vector>

using namespace std;

void GiantRat::draw(SDL_Renderer *renderer, int distance) {
    if (distance == 1) {
        vector<Sint16> pointsX = {
                (Sint16) 278 / 2, (Sint16) (254 / 2),
                (Sint16) (290 / 2),
                (Sint16) (304 / 2), (Sint16) (316 / 2),
                (Sint16) (352 / 2), (Sint16) (328 / 2)
        };
        vector<Sint16> pointsY = {
                (Sint16) (262 / 2), (Sint16) (236 / 2), (Sint16) (164 / 2), (Sint16) (188 / 2),
                (Sint16) (164 / 2), (Sint16) (236 / 2), (Sint16) (262 / 2)
        };

        filledPolygonRGBA(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0, 0, 0, 255);
        polygonColor(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0xFFFFFFFF);

        pointsX = {
                (Sint16) 278 / 2,
                (Sint16) (304 / 2),
                (Sint16) (328 / 2), (Sint16) (304 / 2)
        };
        pointsY = {
                (Sint16) (140 / 2), (Sint16) (152 / 2), (Sint16) (140 / 2), (Sint16) (188 / 2)
        };

        filledPolygonRGBA(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0, 0, 0, 255);
        polygonColor(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0xFFFFFFFF);

        // eyes
        SDL_RenderDrawLine(renderer, 290 / 2, 152 / 2, 298 / 2, 164 / 2);
        SDL_RenderDrawLine(renderer, 316 / 2, 152 / 2, 308 / 2, 164 / 2);

        // paws
        SDL_RenderDrawLine(renderer, 284 / 2, 200 / 2, 284 / 2, 200 / 2 + 14 / 2);
        SDL_RenderDrawLine(renderer, 294 / 2, 200 / 2, 294 / 2, 200 / 2 + 14 / 2);
        SDL_RenderDrawLine(renderer, 312 / 2, 200 / 2, 312 / 2, 200 / 2 + 14 / 2);
        SDL_RenderDrawLine(renderer, 322 / 2, 200 / 2, 322 / 2, 200 / 2 + 14 / 2);

    } else if (distance == 2) {
        vector<Sint16> pointsX = {
                (Sint16) 290 / 2, (Sint16) (278 / 2),
                (Sint16) (296 / 2),
                (Sint16) (304 / 2), (Sint16) (311 / 2),
                (Sint16) (328 / 2), (Sint16) (316 / 2)
        };
        vector<Sint16> pointsY = {
                (Sint16) (208 / 2), (Sint16) (194 / 2), (Sint16) (158 / 2), (Sint16) (170 / 2),
                (Sint16) (158 / 2), (Sint16) (194 / 2), (Sint16) (208 / 2)
        };

        filledPolygonRGBA(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0, 0, 0, 255);
        polygonColor(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0xFFFFFFFF);

        pointsX = {
                (Sint16) 304 / 2,
                (Sint16) (290 / 2),
                (Sint16) (304 / 2), (Sint16) (316 / 2)
        };
        pointsY = {
                (Sint16) (170 / 2), (Sint16) (146 / 2), (Sint16) (152 / 2), (Sint16) (146 / 2)
        };

        filledPolygonRGBA(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0, 0, 0, 255);
        polygonColor(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0xFFFFFFFF);

        // eyes
        SDL_RenderDrawLine(renderer, 296 / 2, 152 / 2, 300 / 2, 158 / 2);
        SDL_RenderDrawLine(renderer, 310 / 2, 152 / 2, 306 / 2, 158 / 2);

        // paws
        SDL_RenderDrawLine(renderer, 294 / 2, 176 / 2, 294 / 2, 176 / 2 + 8 / 2);
        SDL_RenderDrawLine(renderer, 298 / 2, 176 / 2, 298 / 2, 176 / 2 + 8 / 2);
        SDL_RenderDrawLine(renderer, 308 / 2, 176 / 2, 308 / 2, 176 / 2 + 8 / 2);
        SDL_RenderDrawLine(renderer, 312 / 2, 176 / 2, 312 / 2, 176 / 2 + 8 / 2);
    } else if (distance == 3) {
        vector<Sint16> pointsX = {
                (Sint16) 296 / 2, (Sint16) (290 / 2),
                (Sint16) (300 / 2),
                (Sint16) (304 / 2), (Sint16) (306 / 2),
                (Sint16) (316 / 2), (Sint16) (310 / 2)
        };
        vector<Sint16> pointsY = {
                (Sint16) (176 / 2), (Sint16) (168 / 2), (Sint16) (150 / 2), (Sint16) (156 / 2),
                (Sint16) (150 / 2), (Sint16) (168 / 2), (Sint16) (176 / 2)
        };

        filledPolygonRGBA(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0, 0, 0, 255);
        polygonColor(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0xFFFFFFFF);

        pointsX = {
                (Sint16) 296 / 2,
                (Sint16) (304 / 2),
                (Sint16) (310 / 2), (Sint16) (304 / 2)
        };
        pointsY = {
                (Sint16) (144 / 2), (Sint16) (148 / 2), (Sint16) (144 / 2), (Sint16) (156 / 2)
        };

        filledPolygonRGBA(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0, 0, 0, 255);
        polygonColor(renderer, pointsX.data(), pointsY.data(), pointsX.size(), 0xFFFFFFFF);

        // paws
        SDL_RenderDrawLine(renderer, 298 / 2, 160 / 2, 298 / 2, 160 / 2 + 2 / 2);
        SDL_RenderDrawLine(renderer, 299 / 2, 160 / 2, 299 / 2, 160 / 2 + 2 / 2);
        SDL_RenderDrawLine(renderer, 306 / 2, 160 / 2, 306 / 2, 160 / 2 + 2 / 2);
        SDL_RenderDrawLine(renderer, 307 / 2, 160 / 2, 307 / 2, 160 / 2 + 2 / 2);
    }
}

void GiantRat::update(float elapsed) {

}
