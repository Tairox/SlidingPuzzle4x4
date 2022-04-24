#ifndef __menu_h__
#define __menu_h__

#include <SFML/Graphics.hpp>
using namespace sf;

class Menu
{
    Font _font;
    Text _menu[3];
    int _selectedIndex;

    public:
    Menu(int,int);
    ~Menu();
    void MoveUp();
    void MoveDown();
    void Draw(RenderWindow &);

};


#endif