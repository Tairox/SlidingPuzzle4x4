#include "mainmenu.h"
#include "grid.h"
#include <fstream>
#include <iostream>
using namespace std;

class Game
{
    unsigned int height_ = 1920;
    unsigned width_ = 1080;
    RenderWindow window_;
    MainMenu * mainMenu_;
    Grid * grid_;

    ofstream ofs_;
    ifstream ifs_;
    int* sender_;

    bool isInMenu_=true;//au lancement du jeu, on est dans le menu

    Music music_;

public:
    Game();
    ~Game();
    void checkIsInMenu();
    void run();
    void save();
    void charge();
};