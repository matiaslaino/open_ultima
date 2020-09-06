#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include "src/overworld/Tile.h"
#include "src/common/graphics/CGALinearDecodeStrategy.h"
#include "src/common/graphics/EGARowPlanarDecodeStrategy.h"
#include <memory>
#include "src/common/LTimer.h"
#include "src/overworld/Overworld.h"
#include "src/common/Fonts.h"
#include "src/Constants.h"
#include "src/CommandDisplay.h"
#include "src/DungeonScreen.h"
#include "src/town/TownManager.h"
#include "src/town/TownScreen.h"
#include "src/town/TownSpriteTypeLoader.h"

using namespace std;
using namespace OpenUltima;

//Screen dimension constants, this should be a multiple of the regular Ultima resolution to maintain aspect ratio.
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window *gWindow = nullptr;

//The window renderer
SDL_Renderer *gRenderer = nullptr;

shared_ptr<PlayerStatusDisplay> _playerStatusDisplay;
shared_ptr<CommandDisplay> _commandDisplay;

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0)) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        gWindow = SDL_CreateWindow("(Open)Ultima 1: The First Age of Darkness", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }

        //Initialize SDL_ttf
        if (TTF_Init() == -1) {
            printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            success = false;
        }
    }

    return success;
}

bool loadMedia() {
    //Loading success flag
    bool success = true;

    //Nothing to load
    return success;
}

void close() {
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[]) {
    //Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        //Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            auto player = make_shared<Player>(20, 20);
            auto gameContext = make_shared<GameContext>(player);
            auto overworldScreen = make_shared<Overworld>(gameContext, 19, 9);
            auto dungeonScreen = make_shared<DungeonScreen>(gameContext);

            auto egaTilesPath = "F:\\GOGLibrary\\Ultima 1\\EGATILES.BIN";
            auto cgaTilesPath = "F:\\GOGLibrary\\Ultima 1\\CGATILES.BIN";
            auto usingEga = true;

            auto townSpriteLoader = make_shared<TownSpriteTypeLoader>();
            townSpriteLoader->init("F:\\GOGLibrary\\Ultima 1\\EGATOWN.BIN",
                                   make_unique<EGARowPlanarDecodeStrategy>(8, 8).get(),
                                   gRenderer);
            auto townManager = make_shared<TownManager>();
            townManager->init(townSpriteLoader, "F:\\GOGLibrary\\Ultima 1\\TCD.BIN");
            auto town = townManager->getTown(0);

            auto townScreen = make_shared<TownScreen>(gameContext);
            townScreen->setTown(town);

            overworldScreen->init(gRenderer, make_unique<EGARowPlanarDecodeStrategy>(16, 16).get(), egaTilesPath);

            SDL_RenderSetLogicalSize(gRenderer, 320, 200);

            //Keeps track of time between steps
            LTimer stepTimer;
            Fonts::init(gRenderer);

            _playerStatusDisplay = make_shared<PlayerStatusDisplay>(gRenderer, player);
            _commandDisplay = make_shared<CommandDisplay>(gRenderer);
            SDL_Rect commandDisplayBox = {CommandDisplay::POSITION_X, CommandDisplay::POSITION_Y, CommandDisplay::WIDTH,
                                          CommandDisplay::HEIGHT};

            shared_ptr<Dungeon> dungeon = make_shared<Dungeon>("My pet dungeon");
            dungeon->randomize();
            dungeonScreen->setDungeon(dungeon);


            shared_ptr<Screen> currentScreen = static_pointer_cast<Screen>(overworldScreen);

            //While application is running
            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else {
                        if (e.type == SDL_KEYDOWN) {
                            auto pressedKey = e.key.keysym.sym;
                            if (pressedKey == SDLK_PAGEDOWN) {
                                usingEga = !usingEga;
                                if (usingEga) {
                                    overworldScreen->init(gRenderer, make_unique<EGARowPlanarDecodeStrategy>(16, 16).get(),
                                                          egaTilesPath);
                                } else {
                                    overworldScreen->init(gRenderer, make_unique<CGALinearDecodeStrategy>(16, 16).get(),
                                                          cgaTilesPath);
                                }
                            }
                        }

                        currentScreen->handle(e);
                    }
                }

                //Calculate time step
                float timeStep = stepTimer.getTicks();

                //Restart step timer
                stepTimer.start();

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0xAF, 0);
                SDL_RenderClear(gRenderer);

                if (gameContext->getCurrentScreen() == ScreenType::Overworld) {
                    currentScreen = static_pointer_cast<Screen>(overworldScreen);
                } else {
                    currentScreen = static_pointer_cast<Screen>(dungeonScreen);
                }

                currentScreen->update(timeStep);


                overworldScreen->update(timeStep);

                int mapViewPadding = (GAME_VIEW_WIDTH - Overworld::MAP_WIDTH_PX) / 2;
                SDL_Rect mapViewport = {mapViewPadding, mapViewPadding, Overworld::MAP_WIDTH_PX,
                                        Overworld::MAP_HEIGHT_PX};
                SDL_RenderSetViewport(gRenderer, &mapViewport);

                currentScreen->draw(gRenderer);

                SDL_Rect viewport = {PlayerStatusDisplay::POSITION_X, PlayerStatusDisplay::POSITION_Y,
                                     PlayerStatusDisplay::WIDTH, PlayerStatusDisplay::HEIGHT};
                SDL_RenderSetViewport(gRenderer, &viewport);
                _playerStatusDisplay->draw(gRenderer);

                SDL_RenderSetViewport(gRenderer, &commandDisplayBox);
                _commandDisplay->draw(gRenderer);

                //Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}