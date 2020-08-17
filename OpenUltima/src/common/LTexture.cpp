#include "LTexture.h"

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
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

bool LTexture::initEmpty(SDL_Renderer* renderer, int textureWidth, int textureHeight) {
	mTexture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, textureWidth, textureHeight);

	return mTexture != nullptr;
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