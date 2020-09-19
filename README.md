# open_ultima
An open source remake of Ultima 1: First Age of Darkness in very, very, very early stages of development.

This project is the result of my personal goal to better learn SDL and discover newer C++ features, so please keep that in mind when looking at the ugly code!

For compiling use CMake.

Requires (of course) the original game files, you can get them from GOG.com!

Dependencies:
- SDL 2.0.12
- SDL TTF 2.0.15
- SDL Image 2.0.5
- SDL Gfx
- taoJSON (https://github.com/taocpp/json)

Features implemented:
  - Basic overworld.
  - Super basic dungeon crawling.
  - Basic dungeon combat.
  - Town and Castle (empty for now).

![Demo](open_ultima.gif)

## Compiling
1. Install [Microsoft's Vcpkg](https://github.com/Microsoft/vcpkg) for a much simpler way of fetching dependencies (Oh Maven how I miss thee), follow the documentation in git to properly initialize it.
2. Install the dependencies using your target architecture.
    
    For example, fetching them on Windows x64:
    
    `.\vcpck.exe install sdl2:windows-x64`
    
    `.\vcpck.exe install sdl2-ttf:windows-x64`
    
    ...
    
    `.\vcpck.exe install taoJSON:windows-x64`
3. Compile using CMake (I strongly suggest using either Jetbrains's CLion, or VC++)
4. Before executing, make sure you have a valid `config.json` file next to the executable.