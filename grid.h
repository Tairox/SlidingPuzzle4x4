#pragma once
#include <SFML/Graphics.hpp>
#include "state.h"
using namespace sf;

class Grid : public State
{
private:
    bool isInMenu_=true;// car initialement on est dans le menu
    RenderWindow & rw;

public:
    Grid(RenderWindow &);
    void Init() override;
    void ProcessInput() override;
    void Update() override;
    void Draw() override;
};