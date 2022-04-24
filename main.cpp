#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>

#include"fct.h"
#include "menu.h"


int main()
{
    //Window
    RenderWindow window(VideoMode(1920, 1080), "Sliding Puzzle", Style::Titlebar | Style::Close | Style::Resize);
    Event ev; //Contains the event the user has done in the window


    Menu menu(window.getSize().x, window.getSize().y);
    
    //Game loop
    while(window.isOpen())
    {
        while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case Event::KeyReleased:
				switch (ev.key.code)
				{
				case Keyboard::Up:
					menu.MoveUp();
					break;

				case Keyboard::Down:
					menu.MoveDown();
					break;

				case Keyboard::Enter:
					switch (menu.GetPressedItem())
					{
					case 0:
						std::cout << "Play button has been pressed" << std::endl;
						break;
					case 1:
						std::cout << "Option button has been pressed" << std::endl;
						break;
					case 2:
						window.close();
						break;
					}
					break;
				}
				break;

			case sf::Event::Closed:
				window.close();
				break;

			}
		}

        //Update

        //Render

        window.clear(Color::Black);

        //Drawing of the game

        menu.Draw(window);

        window.display(); //Tells app window is done drawing
    }

    //End of application
    return 0;
}
