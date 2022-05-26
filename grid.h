/*------Auteur : Anthony De Sousa
        Contributeurs : Anthony De Sousa & Mattéo Firrone
        Date de dernière modification : 26.05.2022.
Type : Classe dérivée de la classe abstraite 'State'.
Rôle : Jeu de taquin :
       - Génération de grilles solubles de manière aléatoire.
       - Déplacement des cases dans la grille.
       - Détection de fin de partie.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
using namespace sf;
#include <fstream>
using namespace std;

class Grid : public State
{
private:
    Font font_; //police utilisée pour afficher les nombres de la grille
    Font fontClock_; //police utilisée pour afficher l'horloge à côté de la grille
    Font fontButtons_; //police utilisée pour affichier les boutons "back to menu" et "restart"
    Text puzzle_[4][4];//tableau 2D qui contient les 16 chiffres de la grille, on utilise sf::Text car si on utilise unsigned int on ne pourra pas l'afficher
    Sprite imgGrid[4][4]; //tableau 2D contenant l'image découpée en 16 morceaux
    Clock clock_; //chrono
    Time elapsed_; //Temps depuis le lancement de la clock
    Text chrono_; //chrono affichable (en Text)
    Text restartButton_; //bouton restart pour relancer une partie
    Text backToMenuButton_; //bouton pour revenir au menu
    unsigned int seconds_; //secondes du chrono actuel
    unsigned int minutes_; //minutes du chrono actuel
    int* posFree_; //position de la case vide (int* car 2 coordonnées : x et y)
    unsigned int indiceImage_; //indice de l'image tirée aléatoirement afin de faire le puzzle (utilisé afin de ne pas mettre la même image deux fois de suite)
    std::vector<RectangleShape> lines_; // lignes de la grille (à la fois horizontales et verticales)
    //bool isInMenu_=true; pas  utile c dans game mtn il nous faut une méthode checkIsInMenu
    RenderWindow & rw_;
    unsigned int margeW_=560; //marge qu'on laisse de chaque côté de la fenêtre (ça fera donc un carré de 800x800)
    unsigned int margeH_=140;//marge qu'on laisse en haut et en bas
    bool isGridSet_=false; //vrai si la grille est remplie avec des chiffres (une sauvegarde existe) sinon faux
    bool isResolved_=false; //vrai si le taquin est résolu
    int* savePuzzle_; //permet de restaurer une partie antérieure

    bool isExitButtonPressed_=false;
    bool moveNotSaved_=false; //vrai si un mouvement a été fait mais n'est pas encore sauvegardé (utile pour l'autosave)

    SoundBuffer bufferWin_;
    Sound soundWin_;

    Texture bg_texture_;
    Sprite bg_sprite_;

public:
    Grid(RenderWindow &);
    ~Grid();
    void init() override; //redéfinition de init de la classe mère abstraite "State", permet de faire les opérations qui n'ont besoin d'être faites qu'une fois, exemple : dessiner la grille, définir la couleur des chiffres et du background, découper l'image en 16 cases...)
    void processInput() override; //permet de changer les "attributs entrée" (ex: isExitButtonPressed_) de la classe en fonction des entrés utilisateur
    void update() override; //permet de changer les attributs de la classe en fonction des attributs entrée
    void draw() override; //permet de changer ce qui est affiché à l'utilisateur en fonction des attributs de la classe
    void startClock();
    //méthodes spécifiques au puzzle_
    void shuffle();//pour mélanger le taquin (mélanger un taquin soluble fait qu'il est automatiquement soluble
    void moveUp(unsigned int x,unsigned int y);// c'est contre-intuitif : x et y sont inversés (x en abscisse et y en ord)
    void moveDown(unsigned int x,unsigned int y);
    void moveLeft(unsigned int x, unsigned int y);
    void moveRight(unsigned int x, unsigned int y);
    void getFree();// pour avoir la position de la case vide (case 16) int* car x et y à retourner
    bool getMoveNotSaved(); //permet de remonter l'état de l'attribut "moveNotSaved_" afin de faire la sauvegarde dans la classe "Game"
    void setMoveNotSavedToFalse() {moveNotSaved_=false;} //permet de définir l'état de l'attribut "moveNotSaved_" afin de sauvegarder dans la classe "Game" uniquement quand un mouvement est fait
    void checkIsResolved();//permet de vérifier si le taquin est résolu
    int* getPuzzle(); //permet de sauvegarder
    void setPuzzle(int*);//permet de restaurer la sauvegarder
    bool isInMenu();//renvoie faux tout le temps sauf si on appuie sur le boutob "Back to menu" ou son raccourci "B", permet de revenir au menu
    void changeBackground();//permet de changer l'image utilisée par le taquin
    void save(ofstream&);
    void charge (ifstream &);
    };