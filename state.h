#ifndef __state_h__
#define __state_h__

#include <SFML/System/Time.hpp>

//Creation of a generic class that can be used with derived classes
class State
{
public:
    State(){};
    virtual ~State(){};
    virtual void Init() = 0; //Setting up the sprites, texts, positions... "=0 veut dire que la méthode est 'pure' --> elle n'a pas de définition et doit être définie dans les classes filles"
    virtual void ProcessInput() = 0; //Manage key press
    virtual void Update() = 0; //Update elements, l'argument sera utilisé pour faire tourner le jeu a 60fps
    virtual void Draw() = 0;

    virtual void Pause() {};
    virtual void Start() {};
};

#endif