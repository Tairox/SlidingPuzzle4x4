//#pragma once
#include"utils.h"
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

//Pour les méthodes Move : gérer les cas des bords (impossible d'aller à gauche etc)
void Puzzle::MoveUp(unsigned int x, unsigned int y) //pour faire monter la case cliquée d'un cran si la case cliquée est en dessous de la case vide
{
    int* posFree;
    posFree=GetFree();//on récupère la position de la case vide
    if (posFree[0]!=0)//si on est pas sur la première ligne du taquin alors on peut faire l'opération MoveUp
    {
        unsigned int temp=puzzle[x][y];//on prend la case cliquée
        puzzle[x][y]=puzzle[x-1][y];//la case cliquée devient la case du dessus
        puzzle[x-1][y]=temp;//la case du dessous devient la case cliquée
    }
}

void Puzzle::MoveDown(unsigned int x, unsigned int y) //on fait baisser la case cliquée dans la case vide
{
    int* posFree;
    posFree=GetFree();//on récupère la position de la case vide
    if (posFree[0]!=3)//si on est pas sur la dernière ligne du taquin alors on peut faire l'opération MoveUp
    {   
        unsigned int temp=puzzle[x][y];//on prend la case cliquée
        puzzle[x][y]=puzzle[x+1][y];//la case cliquée devient la case du dessous
        puzzle[x+1][y]=temp;//la case du dessus devient la case cliquée
    }
}

void Puzzle::MoveLeft(unsigned int x, unsigned int y) //case cliquée va à gauche
{
    int* posFree;
    posFree=GetFree();//on récupère la position de la case vide
    if (posFree[1]!=0) //si la case vide n'est pas sur la colonne de gauche 
    {
        unsigned int temp=puzzle[x][y];
        puzzle[x][y]=puzzle[x][y-1];
        puzzle[x][y-1]=temp;
    }
    
}

void Puzzle::MoveRight(unsigned int x, unsigned int y) //case cliquée va à droite
{
    unsigned int temp=puzzle[x][y];
    puzzle[x][y]=puzzle[x][y+1];
    puzzle[x][y+1]=temp;
}

int* Puzzle::GetFree()
{
    for(unsigned int i=0;i<4;i++)
   {
      for(unsigned int j=0;j<4;j++)
      {
        if(puzzle[i][j]==16)
        {
            int* pos=new int[2];
            pos[0]=i;
            pos[1]=j;
            return pos;
        }
      }
   }
   return nullptr;//error
}

void Puzzle::Shuffle()
{
    unsigned int i=0;
    while (i<64)
    {
        int* posFree;
        posFree=GetFree();
        unsigned int x=random_at_most(0,3);//génerer un random x [0;3]
        switch (x)
        {
        case 0:
           MoveUp(posFree[0]-1,posFree[1]); //on simule un clic sur la case en dessous de la case vide (ce qui fera "remonter" le chiffre et "baisser" la case vide)
            break;
        case 1:
            MoveDown(posFree[0]+1,posFree[1]);//clic au dessus de la case vide
            break;
        case 2:
            MoveLeft(posFree[0],posFree[1]-1); //clic à gauche de la case vide
            break;
        case 3:
            MoveRight(posFree[0],posFree[1]+1);// clic à droite de la case vide
            break;
        default:
            //error
            break;
        }
    }
}