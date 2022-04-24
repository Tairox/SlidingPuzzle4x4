#include "Menu.h"


Menu::Menu(int width, int height)
{
	if (!_font.loadFromFile("arial.ttf"))
	{
		// handle error
	}

	_text[0].setFont(_font);
	_text[0].setColor(sf::Color::Red);
	_text[0].setString("Play");
	_text[0].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 1));

	_text[1].setFont(_font);
	_text[1].setColor(sf::Color::White);
	_text[1].setString("New Game");
	_text[1].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 2));

	_text[2].setFont(_font);
	_text[2].setColor(sf::Color::White);
	_text[2].setString("Exit");
	_text[2].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 3));

	_selectedIndex = 0;
}

Menu::~Menu()
{
    //Nothing to do here yet.
}

void Menu::MoveUp()
{
	if (_selectedIndex - 1 >= 0) //If we are under 0 we have to MoveDown.
	{
		_text[_selectedIndex].setColor(Color::White);
		_selectedIndex--;
		_text[_selectedIndex].setColor(Color::Red);
	}
}

void Menu::MoveDown() 
{
	if (_selectedIndex + 1 < 3) //If we are above 3 we have to MoveUP.
	{
		_text[_selectedIndex].setColor(sf::Color::White);
		_selectedIndex++;
		_text[_selectedIndex].setColor(sf::Color::Red);
	}
}

void Menu::Draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(_text[i]);
	}
}