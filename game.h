#include "mainmenu.h"
#include "stateman.h"

class Game
{
    MainMenu * mainMenu_; //Agrégation
    StateMan * stateManager_; //Agrégation
public:
    Game();
    ~Game();
    void Run();
};