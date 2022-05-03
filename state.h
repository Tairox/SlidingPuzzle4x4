#ifndef __state_h__
#define __state_h__

#include <SFML/System/Time.hpp>

//Création d'une classe abstraite afin de définir les différents états du jeu.
//Les méthodes virtuelles doivent obligatoirement être définies dans la classe fille.
class State
{
public:
    virtual void init() = 0; //Setting up the sprites, texts, positions... "'=0' veut dire que la méthode est 'pure' --> elle n'a pas de définition et doit être définie dans les classes filles"
    virtual void processInput() = 0; //Manage key press...
    virtual void update() = 0; //update elements...
    virtual void draw() = 0; //Draw in the RenderWindow...
};

#endif