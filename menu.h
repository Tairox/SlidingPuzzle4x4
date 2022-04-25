#ifndef __menu_h__
#define __menu_h__

#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>

class Menu
{
    Font font_;
    Text text_[3];
    int selectedIndex_;

    public:
    Menu(int,int);
    ~Menu();
    void MoveUp();
    void MoveDown();
    void Draw(RenderWindow &);
    int GetPressedItem() { return selectedIndex_; }

};


#endif