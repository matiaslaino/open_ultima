#include "Thief.h"
#include "SDL2_gfxPrimitives.h"

void Thief::draw(SDL_Renderer *renderer, int distance) {
    // middle x: 152
    // floor y = 131
    int MIDDLE_X = 152;
    if (distance == 1) {

        // body - left
        auto *pointsX = new Sint16[]{
                (Sint16) MIDDLE_X, (Sint16) (MIDDLE_X),
                (Sint16) (139),
                (Sint16) (115), (Sint16) (115),
                (Sint16) (139)
        };
        auto pointsY = new Sint16[]{
                (Sint16) 63, (Sint16) (122), (Sint16) (131), (Sint16) (131),
                (Sint16) (67), (Sint16) (54)
        };

        filledPolygonRGBA(renderer, pointsX, pointsY, 6, 0, 0, 0, 255);
        polygonColor(renderer, pointsX, pointsY, 6, 0xFFFFFFFF);

        delete[] pointsX;

        // body - right (same Y's)
        pointsX = new Sint16[]{
                (Sint16) MIDDLE_X, (Sint16) (MIDDLE_X),
                (Sint16) (164),
                (Sint16) (188), (Sint16) (188),
                (Sint16) (164)
        };

        filledPolygonRGBA(renderer, pointsX, pointsY, 6, 0, 0, 0, 255);
        polygonColor(renderer, pointsX, pointsY, 6, 0xFFFFFFFF);

        delete[] pointsX;
        delete[] pointsY;

        // head
        pointsX = new Sint16[]{
                (Sint16) MIDDLE_X,
                (Sint16) (139),
                (Sint16) (139),
                (Sint16) (152),
                (Sint16) (164), (Sint16) (164)
        };

        pointsY = new Sint16[]{
                (Sint16) 63, (Sint16) (54), (Sint16) (39), (Sint16) (30),
                (Sint16) (39), (Sint16) (54)
        };

        filledPolygonRGBA(renderer, pointsX, pointsY, 6, 0, 0, 0, 255);
        polygonColor(renderer, pointsX, pointsY, 6, 0xFFFFFFFF);

        delete[] pointsX;
        delete[] pointsY;

        // helmet "opening"
        pointsX = new Sint16[]{
                (Sint16) 164,
                (Sint16) (MIDDLE_X),
                (Sint16) (139),
                (Sint16) (MIDDLE_X)
        };

        pointsY = new Sint16[]{
                (Sint16) 39, (Sint16) (35), (Sint16) (39), (Sint16) (57)
        };

        filledPolygonRGBA(renderer, pointsX, pointsY, 4, 0, 0, 0, 255);
        polygonColor(renderer, pointsX, pointsY, 4, 0xFFFFFFFF);

        delete[] pointsX;
        delete[] pointsY;
    } else if (distance == 2) {


    }
}

void Thief::update(float elapsed) {

}
