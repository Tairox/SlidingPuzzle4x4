/*------Auteur : Mattéo FIRRONE
        Contributeurs : Mattéo FIRRONE & Anthony De Sousa
        Date de dernière modification : 26.05.2022.
Type : Agrégat des classes 'MainMenu' & 'Grid'.
Rôle : Créer l'environnement nécessaire pour faire tourner l'application :
       - Mise en place de la fenêtre de l'application.
       - Contrôle des passages du menu à la grille.
       - S'occupe des chargements et des sauvegardes.
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
    //Attributs relatifs à la fenêtre de l'application :
    unsigned int height_ = 1920;
    unsigned width_ = 1080;
    RenderWindow window_;

    //Déclaration des deux composants de l'agrégat :
    MainMenu * mainMenu_;
    Grid * grid_;

    //Variables d'E/S pour la sauvegarde et le chargemement :
    ofstream ofs_;
    ifstream ifs_;

    //Booléen pour le controle du menu et de la grille :
    bool isInMenu_=true;    //L'utilisateur se trouve dans le menu au lancement du jeu.

    //Musique du jeu(choisie de manière aléatoire dans une banque de musique)
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