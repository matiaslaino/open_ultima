/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "src/overworld/Tile.h"
#include "src/CGALinearDecodeStrategy.h"
#include "src/EGARowPlanarDecodeStrategy.h"
#include <memory>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "src/common/LTimer.h"
#include "src/TileTypeLoader.h"
#include "src/overworld/Overworld.h"

using namespace std;
using namespace OpenUltima;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("(Open)Ultima 1: The First Age of Darkness", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

//struct SDL_Deleter {
//	void operator()(SDL_Surface* ptr) { if (ptr) SDL_FreeSurface(ptr); }
//	void operator()(SDL_Texture* ptr) { if (ptr) SDL_DestroyTexture(ptr); }
//	void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
//	void operator()(SDL_Window* ptr) { if (ptr) SDL_DestroyWindow(ptr); }
//	void operator()(SDL_RWops* ptr) { if (ptr) SDL_RWclose(ptr); }
//};

//std::vector<uint8_t> load_file(std::string const& filepath)
//{
//	std::ifstream ifs(filepath, std::ios::binary | std::ios::ate);
//
//	if (!ifs)
//		throw std::runtime_error(filepath + ": " + std::strerror(errno));
//
//	auto end = ifs.tellg();
//	ifs.seekg(0, std::ios::beg);
//
//	auto size = std::size_t(end - ifs.tellg());
//
//	if (size == 0) // avoid undefined behavior 
//		return {};
//
//	std::vector<uint8_t> buffer(size);
//
//	if (!ifs.read((char*)buffer.data(), buffer.size()))
//		throw std::runtime_error(filepath + ": " + std::strerror(errno));
//
//	return buffer;
//}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			auto player = make_shared<Player>(20, 20);
			auto overworld = make_unique<Overworld>(player, 19, 9);
			overworld->init(gRenderer);

			SDL_RenderSetLogicalSize(gRenderer, 320, 200);

			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			//Keeps track of time between steps
			LTimer stepTimer;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else {
						overworld->handle(e);
					}
				}

				//Calculate time step
				float timeStep = stepTimer.getTicks() / 1000.f;

				//Restart step timer
				stepTimer.start();

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				overworld->update(timeStep);
				overworld->draw(gRenderer);
				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}