#pragma once
#include <SDL.h>
#include <string>

//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile(std::string path);

    bool initEmpty(SDL_Renderer* renderer, int textureWidth, int textureHeight);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};
