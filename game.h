#include "mainmenu.h"
#include "grid.h"

class Game
{
    unsigned int height = 1920;
    unsigned width = 1080;
    RenderWindow window_;
    MainMenu * mainMenu_;
    Grid * grid;

    bool isInMenu=true;//au lancement du jeu, on est dans le menu

    //MainMenu mainMenu_; //Composition

public:
    Game();
    ~Game();
    void CheckIsInMenu();
    void run();
};