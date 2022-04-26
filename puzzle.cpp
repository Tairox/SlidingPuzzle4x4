#include "puzzle.h"

Puzzle::Puzzle() //création d'un taquin résolu 1,2,3,4...16 avec 16 étant la position de la case vide
{
    unsigned int i=1;
    for(unsigned int j=0;j<4;j++)
   {
      for(unsigned int k=0;k<4;k++)
      {
         puzzle[j][k]=i;
         i++;
      }
   }
}

void Puzzle::MoveUp(unsigned int x, unsigned int y) //pour faire monter la case cliquée d'un cran si la case cliquée est en dessous de la case vide
{
    unsigned int temp=puzzle[x][y];//on prend la case cliquée
    puzzle[x][y]=puzzle[x-1][y];//la case cliquée devient la case du dessus
    puzzle[x-1][y]=temp;//la case du dessous devient la case cliquée
}

void Puzzle::MoveDown(unsigned int x, unsigned int y) //on fait baisser la case cliquée dans la case vide
{
    unsigned int temp=puzzle[x][y];//on prend la case cliquée
    puzzle[x][y]=puzzle[x+1][y];//la case cliquée devient la case du dessous
    puzzle[x+1][y]=temp;//la case du dessus devient la case cliquée
}

void Puzzle::MoveLeft(unsigned int x, unsigned int y) //case cliquée va à gauche
{
    unsigned int temp=puzzle[x][y];
    puzzle[x][y]=puzzle[x][y-1];
    puzzle[x][y-1]=temp;
}

void Puzzle::MoveRight(unsigned int x, unsigned int y) //case cliquée va à droite
{
    unsigned int temp=puzzle[x][y];
    puzzle[x][y]=puzzle[x][y+1];
    puzzle[x][y+1]=temp;
}