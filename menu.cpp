#include "Menu.h"


Menu::Menu(int width, int height)
{
	if (!_font.loadFromFile("arial.ttf"))
	{
		// handle error
	}

	_menu[0].setFont(_font);
	_menu[0].setColor(sf::Color::Red);
	_menu[0].setString("Play");
	_menu[0].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 1));

	_menu[1].setFont(_font);
	_menu[1].setColor(sf::Color::White);
	_menu[1].setString("Options");
	_menu[1].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 2));

	_menu[2].setFont(_font);
	_menu[2].setColor(sf::Color::White);
	_menu[2].setString("Exit");
	_menu[2].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 3));

	_selectedIndex = 0;
}