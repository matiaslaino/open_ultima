#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>

//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();
    LTexture(SDL_Texture* texture, int width, int height);

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile(std::string path);

    bool loadFromRenderedText(TTF_Font* font, SDL_Renderer* renderer, std::string textureText, SDL_Color textColor);
    bool loadFromColor(SDL_Renderer* renderer, int width, int height, int r, int g, int b, int a);
    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);

    //Gets image dimensions
    int getWidth();
    int getHeight();

    SDL_Texture* getRawTexture();

private:    
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};
