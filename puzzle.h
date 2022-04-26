#pragma once
class Puzzle
{
    unsigned int puzzle[4][4];
public:
    Puzzle();
    void Shuffle();//pour mélanger le taquin (mélanger un taquin soluble fait qu'il est automatiquement soluble
    void MoveUp(unsigned int x,unsigned int y);// c'est contre-intuitif : x et y sont inversés (x en abscisse et y en ord)
    void MoveDown(unsigned int x,unsigned int y);
    void MoveLeft(unsigned int x, unsigned int y);
    void MoveRight(unsigned int x, unsigned int y);
    int* GetFree();// pour avoir la position de la case vide (case 16) int* car x et y à retourner
};