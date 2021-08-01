![cendric logo](images/logo.png)
# Cendric - RPG Platformer

*Cendric* combines RPG and Platformer elements in one game, featuring both a sidescroller and top-down view. The player follows the story of a boy with no memory and discovers the magical but dangerous world of Admantris.

## Development and Release

The Steam page for Cendric is online: 
http://store.steampowered.com/app/681460/Cendric/

You can also get Cendric on itch.io:
https://ironbell.itch.io/cendric

Cendric was released on the 2. March 2018.

## Wiki

The official Cendric wiki is hosted on Gamepedia:
https://cendric.gamepedia.com

Feel free to contribute!

## Discord

You can join our community discord server here:
https://discord.gg/6mJARSJ

## Screenshots

For the newest screenshots, check out http://cendric.ch/screenshots.

## Gameplay

Cendric moves through the world on a 2D map and interacts with NPCs to trade or accept quests. At certain places, he can enter levels in which he fights enemies, collects items and completes tricky platforming challenges. To accomplish all this, Cendric can master various spells from different classes of magic.

## Features

- Interactive Levels: Some of Cendric's spells affect the levels and change his surroundings in the levels.
- Modifiable Spells: All spells can be modified using gems to make them stronger or behave in new ways.
- Special Effects: The game contains particle effects, a water simulation and simple lighting.
- Localization: All texts in the game are available in English, German and Swiss German.

![cendric icons](images/icons.png)

## Current stable build

Latest release builds are available for Windows x64, macOS and Ubuntu. However, feel free to try and compile *Cendric* on any platform.

[Cendric v1.0.4](https://github.com/tizian/Cendric2/releases/download/1.0.4/Cendric_v1.0.4_Windows.zip) (Windows x64)

[Cendric v1.0.4](https://github.com/tizian/Cendric2/releases/download/1.0.4/Cendric_v1.0.4_MacOS.zip) (macOS)

[Cendric v1.0.4](https://github.com/tizian/Cendric2/releases/download/1.0.4/Cendric_v1.0.4_Linux.tar.gz) (Ubuntu x64)


A list of all builds is available [here](https://github.com/tizian/Cendric2/releases).

## How to compile

The recommended way to compile the code is to use [**CMake**](https://cmake.org/), which automatically generates project files for your favourite IDE or build system:
```
git clone https://github.com/tizian/Cendric2.git --recursive
cd Cendric2
mkdir build
cd build
cmake ..
cmake --build .
```

### CMake Options

| Variable                           | Type   | Default | Description                                                  |
|------------------------------------|--------|---------|--------------------------------------------------------------|
| `CENDRIC_BUILD_SQLITE_SHELL`       | Option | OFF     | Build SQLite shell on Windows platform?                      |
| `CENDRIC_BUILD_DIALOGUE_TOOL`      | Option | ON      | Build Dialogue Tool on Windows platform?                     |
| `CENDRIC_STEAM`                    | Option | OFF     | Include steamworks API?                                      |
| `CENDRIC_EXTERNAL_DOCUMENT_FOLDER` | Option | OFF     | Use external documents folder?                               |
| `CENDRIC_GERMAN`                   | Option | OFF     | Use German as default language?                              |
| `USE_SYSTEM_SFML`                  | Option | OFF     | Use system SFML lib instead of internal                      |
| `USE_SYSTEM_PATHS`                 | Option | OFF     | Use system paths for loading resources instead of local ones |

## Used Libraries

- [SFML](https://www.sfml-dev.org/) : Window creation, rendering and sound
- [SQLite](https://www.sqlite.org/) : Database for translations and items
- [Lua](https://www.lua.org/work/) and [LuaBridge](https://github.com/vinniefalco/LuaBridge) : Scripting
- [TinyXML 2](http://www.grinninglizard.com/tinyxml2/index.html) : XML parsing
- [Dear ImGui](https://github.com/ocornut/imgui) : GUI for the Dialogue Tool
- [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml) : Dear ImGui binding for SFML

## License

The code of this repository uses a MIT license.

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />Game assets (images, and fonts) found in the "res" folder are licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>. Give attribution to Isa Roesch & Tizian Zeltner, if you're going to use them. 
The sound and music files found in the said folder are licenced under a CC0 (public domain) or a CC by SA licence. See the game's credits for the attribution notice. 
Tracks created by the main composer for the game, Matthew Harnage, can only be used with his explicit permission as well as the permission of Isabelle Roesch.
Tracks created by Susanne Aubert and Isabelle Roesch can only be used with their explicit permission.

