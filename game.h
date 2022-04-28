#include "mainmenu.h"
#include "grid.h"
#include <fstream>
#include <iostream>
using namespace std;

class Game
{
    unsigned int height = 1920;
    unsigned width = 1080;
    RenderWindow window_;
    MainMenu * mainMenu_;
    Grid * grid;

    ofstream ofs;

    bool isInMenu=true;//au lancement du jeu, on est dans le menu

    //MainMenu mainMenu_; //Composition

public:
    Game();
    ~Game();
    void CheckIsInMenu();
    void run();
    void save();
};