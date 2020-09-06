cmake_minimum_required(VERSION 3.17)

project(open_ultima)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)

#file(GLOB_RECURSE open_ultima_SRC
#        *.h
#        *.cpp
#        )

add_executable(open_ultima main.cpp src/common/graphics/CGALinearDecodeStrategy.cpp
        src/common/graphics/EGARowPlanarDecodeStrategy.cpp
        src/CommandDisplay.cpp
        src/DungeonScreen.cpp
        src/GameContext.cpp
        src/Player.cpp
        src/PlayerStatusDisplay.cpp
        src/Screen.cpp
        src/common/ShapeUtils.cpp
        src/overworld/TileTypeLoader.cpp
        src/common/Fonts.cpp
        src/common/graphics/LTexture.cpp
        src/common/LTimer.cpp
        src/dungeon/Door.cpp
        src/dungeon/Dungeon.cpp
        src/overworld/Overworld.cpp
        src/overworld/OverworldSpriteType.cpp
        src/overworld/Tile.cpp
        src/overworld/TileAnimation.cpp
        src/common/graphics/SpriteSheetLoader.cpp
        src/town/TownScreen.cpp src/town/TownScreen.h
        src/town/TownSpriteType.cpp src/town/TownSpriteType.h
        src/town/TownSpriteTypeLoader.cpp src/town/TownSpriteTypeLoader.h
        src/town/Town.cpp src/town/Town.h
        src/town/TownManager.cpp src/town/TownManager.h
        src/town/TownTile.cpp src/town/TownTile.h
        )

target_link_libraries(open_ultima PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(open_ultima PRIVATE SDL2::SDL2_image)
target_link_libraries(open_ultima PRIVATE SDL2::SDL2_ttf)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})