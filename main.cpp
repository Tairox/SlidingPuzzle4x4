#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>

#include "menu.h"


int main()
{
    //Window
    RenderWindow window_menu(VideoMode(1920, 1080), "Sliding Puzzle", Style::Default);
	window_menu.setFramerateLimit(60);
    Event ev; //Contains the event the user has done in the window
	
	Image icon;
	if(!icon.loadFromFile("img/icon.png"))
	{
		std::cout<<"Could not load icon"<<std::endl;
	}
	window_menu.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); //permet de définir l'icône de la fenêtre à partir d'un sf::Image

	Texture bg_texture;
	if(!bg_texture.loadFromFile("img/background.jpg"))
	{
		std::cout<<"Could not load background texture"<<std::endl;
	}
	Sprite bg_sprite(bg_texture);

    Menu menu(window_menu.getSize().x, window_menu.getSize().y);

	//Title
	Text title;
	Font font;
	Vector2f titlePosition(0,0);
	if (!font.loadFromFile("font/Walk-Around-the-Block.ttf"))
	{
		// handle error
	}
	title.setFont(font);
	title.setColor(sf::Color::Red);
	title.setString("Sliding Puzzle");
	title.setCharacterSize(150);
	title.setPosition(titlePosition);

	float xVelocity = 3;
    
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
				case Keyboard::Escape:
					window_menu.close();
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

		//Physics
		if(titlePosition.x <0 || titlePosition.x > window_menu.getSize().x - title.getLocalBounds().width)
		{
			xVelocity *= -1;
		}
		titlePosition.x += xVelocity;
		title.setPosition(titlePosition);

        //Update

        //Render

        window_menu.clear(Color::Black);

        //Drawing of the game
		window_menu.draw(bg_sprite);
		window_menu.draw(title);
        menu.Draw(window_menu);

        window_menu.display(); //Tells app window is done drawing
    }

    //End of application
    return 0;
}
