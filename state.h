/*------Auteur : Mattéo FIRRONE
        Date de dernière modification : 26.05.2022.
Type : Classe abstraite.
Rôle : Template permettant de créer les fenêtres de l'application à travers les méthodes suivantes :
       - 'init' pour initialiser les éléments de la fenêtre.
       - 'processInput' pour gérer les actions de l'utilisateur.
       - 'update' pour mettre à jours les modifications de la fenêtre.
       - 'draw' pour dessiner le résultat de la mise à jour.
*/

#ifndef __state_h__
#define __state_h__

#include <SFML/System/Time.hpp>

//Création d'une classe abstraite afin de définir les différents états du jeu.
//Les méthodes virtuelles doivent obligatoirement être définies dans les classe dérivées.
class State
{
public:
    virtual void init() = 0;
    virtual void processInput() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
};

#endif