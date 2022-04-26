#include "mainmenu.h"

class Game
{
    RenderWindow window_;
    MainMenu * mainMenu_;

    //MainMenu mainMenu_; //Composition

public:
    Game();
    ~Game();
    void Run();
};