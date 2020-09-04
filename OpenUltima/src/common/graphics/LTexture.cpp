#include "LTexture.h"

LTexture::LTexture()
{
	//Initialize
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

LTexture::LTexture(SDL_Texture* texture, int width, int height)
{
	//Initialize
	mTexture = texture;
	mWidth = width;
	mHeight = height;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	return false;
	////Get rid of preexisting texture
	//free();

	////The final texture
	//SDL_Texture* newTexture = NULL;

	////Load image at specified path
	//SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	//if (loadedSurface == NULL)
	//{
	//	printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	//}
	//else
	//{
	//	//Color key image
	//	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	//	//Create texture from surface pixels
	//	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	//	if (newTexture == NULL)
	//	{
	//		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	//	}
	//	else
	//	{
	//		//Get image dimensions
	//		mWidth = loadedSurface->w;
	//		mHeight = loadedSurface->h;
	//	}

	//	//Get rid of old loaded surface
	//	SDL_FreeSurface(loadedSurface);
	//}

	////Return success
	//mTexture = newTexture;
	//return mTexture != NULL;
}

bool LTexture::loadFromColor(SDL_Renderer* renderer, int width, int height, int r, int g, int b, int a)
{
	//Get rid of preexisting texture
	free();

	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, r, g, b, a);
	if (surface == nullptr)
	{
		printf("Unable to render color surface! SDL_ttf Error: %s\n", SDL_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(renderer, surface);
		if (mTexture == nullptr)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = surface->w;
			mHeight = surface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(surface);
	}

	//Return success
	return mTexture != nullptr;
}


bool LTexture::loadFromRenderedText(TTF_Font* font, SDL_Renderer* renderer, const std::string& textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == nullptr)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

SDL_Texture* LTexture::getRawTexture()
{
	return mTexture;
}
