#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>

#include"fct.h"
#include "menu.h"


int main()
{
    //Window
    RenderWindow window_menu(VideoMode(1920, 1080), "Sliding Puzzle", Style::Fullscreen);
    Event ev; //Contains the event the user has done in the window

	Texture bg_texture;
	if(!bg_texture.loadFromFile("img/background.jpg"))
	{
		std::cout<<"Could not load background texture"<<std::endl;
	}
	Sprite bg_sprite(bg_texture);

    Menu menu(window_menu.getSize().x, window_menu.getSize().y);
    
    //Game loop
    while(window_menu.isOpen())
    {
        while (window_menu.pollEvent(ev))
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
						window_menu.close();
						break;
					}
					break;
				}
				break;

			case sf::Event::Closed:
				window_menu.close();
				break;

			}
		}

        //Update

        //Render

        window_menu.clear(Color::Black);

        //Drawing of the game
		
		window_menu.draw(bg_sprite);
        menu.Draw(window_menu);

        window_menu.display(); //Tells app window is done drawing
    }

    //End of application
    return 0;
}
