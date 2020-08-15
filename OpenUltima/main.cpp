/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "src/overworld/TileType.h"
#include "src/overworld/Tile.h"
#include "src/CGALinearRenderStrategy.h"
#include <memory>
#include <filesystem>
#include <iostream>>
#include <fstream>

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
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
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

struct SDL_Deleter {
	void operator()(SDL_Surface* ptr) { if (ptr) SDL_FreeSurface(ptr); }
	void operator()(SDL_Texture* ptr) { if (ptr) SDL_DestroyTexture(ptr); }
	void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
	void operator()(SDL_Window* ptr) { if (ptr) SDL_DestroyWindow(ptr); }
	void operator()(SDL_RWops* ptr) { if (ptr) SDL_RWclose(ptr); }
};

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

			auto tileType = make_shared<TileType>(TileType(11, 16, 16, 
				{ 
					0b00110011, 0, 0, 0, 
					0, 0b00110011, 0, 0,
					0, 0, 0b00110011, 0,
					0, 0, 0, 0b00110011,
					0b00110011, 0, 0, 0,
					0, 0b00110011, 0, 0,
					0, 0, 0b00110011, 0,
					0, 0, 0, 0b00110011,
					0b00110011, 0, 0, 0,
					0, 0b00110011, 0, 0,
					0, 0, 0b00110011, 0,
					0, 0, 0, 0b00110011,
					0b00110011, 0, 0, 0,
					0, 0b00110011, 0, 0,
					0, 0, 0b00110011, 0,
					0, 0, 0, 0b00110011,
				}));
			
			auto tileType2 = make_shared<TileType>(TileType(12, 16, 16, 
				{ 
					0x00, 0x10, 0x00, 0x00,
					0x00, 0x00, 0x04, 0x00,
					0x40, 0x00, 0x00, 0x00,
					0x00, 0x01, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x40,
					0x10, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x00,
					0x00, 0x10, 0x00, 0x00,
					0x00, 0x00, 0x00, 0x40,
					0x04, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x40, 0x00,
					0x00, 0x00, 0x00, 0x04,
					0x00, 0x00, 0x00, 0x00,
					0x10, 0x00, 0x00, 0x00,
					0x00, 0x00, 0x01, 0x00
				}));
			//auto tile = make_unique<Tile>(Tile(0, 0, tileType));
			//auto tile2 = make_unique<Tile>(Tile(16, 0, tileType2));

			//auto cgatilesContent = load_file("F:\\GOGLibrary\\Ultima 1\\CGATILES.BIN");
			//for (uint8_t byte : cgatilesContent) {

			//}

			SDL_RWops* file = SDL_RWFromFile("F:\\GOGLibrary\\Ultima 1\\CGATILES.BIN", "r+b");
			uint8_t gData[64];
			std::vector<OpenUltima::Tile> tiles = {};
			auto indexY = 0;
			auto indexX = 0;
			for (int i = 0; i < (0xD00 / 64); i++)
			{
				SDL_RWread(file, &gData[0], 1, 64);
				vector<uint8_t> bytes(begin(gData), end(gData));
				auto tileType = make_shared<TileType>(TileType(i, 16, 16, bytes));
				
				indexX += 16;
				if (indexX > 200) {
					indexX = 0;
					indexY += 16;
				}

				auto tile = OpenUltima::Tile(indexX, indexY, tileType, make_shared<CGALinearRenderStrategy>(CGALinearRenderStrategy()));
				tiles.push_back(tile);
			}

			SDL_RWclose(file);
			//auto renderer = unique_ptr<SDL_Renderer, SDL_Deleter>(gRenderer);
			SDL_RenderSetLogicalSize(gRenderer, 320, 200);


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
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				/*tile->Draw(gRenderer);
				tile2->Draw(gRenderer);
				*/

				for (auto tile : tiles)
				{
					tile.Draw(gRenderer);
				}

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}