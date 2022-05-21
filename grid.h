#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
using namespace sf;

class Grid : public State
{
private:
    Font font_;
    Font fontClock_;
    Font fontButtons_;
    Text puzzle_[4][4];//on utilise sf::Text car si on utilise unsigned int on ne pourra pas l'afficher
    Sprite imgGrid[4][4];
    Clock clock_; //chrono
    Time elapsed_; //Temps depuis le lancement de la clock
    Text chrono_;
    Text restartButton_;
    Text backToMenuButton_;
    unsigned int seconds_; //secondes de la session d'avant (à restaurer via sauvegarde)
    unsigned int minutes_;
    int* posFree_;
    unsigned int indiceImage_;
    std::vector<RectangleShape> lines_; // lignes de la grille (à la fois horizontales et verticales)
    //bool isInMenu_=true; pas  utile c dans game mtn il nous faut une méthode checkIsInMenu
    RenderWindow & rw_;
    unsigned int margeW_=560; //marge qu'on laisse de chaque côté de la fenêtre (ça fera donc un carré de 800x800)
    unsigned int margeH_=140;//marge qu'on laisse en haut et en bas
    bool isGridSet_=false;
    bool isResolved_=false;
    int* savePuzzle_;

    bool isExitButtonPressed_=false;

    SoundBuffer bufferWin_;
    Sound soundWin_;

    Texture bg_texture_;
    Sprite bg_sprite_;

public:
    Grid(RenderWindow &);
    ~Grid();
    void init() override;
    void processInput() override;
    void update() override;
    void draw() override;
    void startClock();
    //méthodes spécifiques au puzzle_
    void shuffle();//pour mélanger le taquin (mélanger un taquin soluble fait qu'il est automatiquement soluble
    void moveUp(unsigned int x,unsigned int y);// c'est contre-intuitif : x et y sont inversés (x en abscisse et y en ord)
    void moveDown(unsigned int x,unsigned int y);
    void moveLeft(unsigned int x, unsigned int y);
    void moveRight(unsigned int x, unsigned int y);
    void getFree();// pour avoir la position de la case vide (case 16) int* car x et y à retourner
    void checkIsResolved();
    int* getPuzzle();
    void setPuzzle(int*);
    bool isInMenu();
    void changeBackground();
    };