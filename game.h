/*------Auteur : Mattéo FIRRONE
        Contributeurs : Mattéo FIRRONE & Anthony De Sousa
        Date de dernière modification : 26.05.2022.
Type : Agrégat des classes 'MainMenu' & 'Grid'.
Rôle : Crée l'environnement nécéssaire pour faire tourner l'application :
       - Mise en place de la fenêtre de l'application.
       - Contrôle le menu et la grille de jeu.
       - S'occupe des chargements et sauvegardes.
*/

#ifndef __game_h__
#define __game_h__

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

    bool isInMenu_=true;//L'utilisateur se trouve dans le menu au lancement du jeu.

    Music music_;

public:
    Game();
    ~Game();
    void checkIsInMenu();
    void run();
    void save();
    void charge();
};

#endif