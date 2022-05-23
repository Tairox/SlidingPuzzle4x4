# SlidingPuzzle4x4
Sliding Puzzle 4x4 using SFML library in C++

## How to play

### The game
The goal of the game is to reassamble the puzzle in this order :<br>
| 1 | 2 | 3 | 4 |
|---|:--:|--:|---:|
| 5 |  6 | 7 | 8 |
| 9 | 10 | 11 | 12 |
| 13 |  14 | 15 |  |

In order to do so, you will be able to click on the tiles next to the empty one in order to make the number clicked jump into the empty space.

### Shortcuts

Escape : Quit the game or return in menu
B : Back to menu
E : Exit
N : New game
P : Play
R : Restart

## How the project was coded

### Language
The project was coded using the SFML library and using __C++20__ syntax and operators.<br>
In order to compile these files you will need to donwload a C++ compiler and the SFML libraries.

### Dependencies
We used a static version of the SFML library which means that we don't include any DLL files in this project apart from "*openal32.dll*".<br>
**This DLL is only required if you use _Windows_.**

### Libraries used

Mac/Linux :<br>
`-L<libFolderOfSFML> -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system`


Windows :<br>
`-L<libFolderOfSFML> -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lfreetype  -lwinmm -lgdi32 -mwindows -lsfml-main -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg`