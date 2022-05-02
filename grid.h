#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
using namespace sf;

class Grid : public State
{
private:
    Font font;
    Text puzzle[4][4];//on utilise sf::Text car si on utilise unsigned int on ne pourra pas l'afficher
    int* PosFree;
    std::vector<RectangleShape> lines; // lignes de la grille (à la fois horizontales et verticales)
    //bool isInMenu_=true; pas  utile c dans game mtn il nous faut une méthode CheckIsInMenu
    RenderWindow & rw;
    unsigned int margeW=560; //marge qu'on laisse de chaque côté de la fenêtre (ça fera donc un carré de 800x800)
    unsigned int margeH=140;//marge qu'on laisse en haut et en bas
    bool isGridSet=false;
    bool isResolved=false;
    int* savePuzzle_;

    bool isExitButtonPressed=false;

    SoundBuffer bufferWin_;
    Sound soundWin_;

public:
    Grid(RenderWindow &);
    ~Grid();
    void Init() override;
    void ProcessInput() override;
    void Update() override;
    void Draw() override;
    //méthodes spécifiques au puzzle
    void Shuffle();//pour mélanger le taquin (mélanger un taquin soluble fait qu'il est automatiquement soluble
    void MoveUp(unsigned int x,unsigned int y);// c'est contre-intuitif : x et y sont inversés (x en abscisse et y en ord)
    void MoveDown(unsigned int x,unsigned int y);
    void MoveLeft(unsigned int x, unsigned int y);
    void MoveRight(unsigned int x, unsigned int y);
    void SetFree();// pour avoir la position de la case vide (case 16) int* car x et y à retourner
    void checkIsResolved();
    int* getPuzzle();
    void setPuzzle(int*);
    bool isInMenu();
    };