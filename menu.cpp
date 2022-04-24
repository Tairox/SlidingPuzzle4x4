#include "Menu.h"


Menu::Menu(int width, int height)
{
	if (!font_.loadFromFile("font/arial.ttf"))
	{
		// handle error
	}

	text_[0].setFont(font_);
	text_[0].setColor(sf::Color::Red);
	text_[0].setString("Play");
	text_[0].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 1));

	text_[1].setFont(font_);
	text_[1].setColor(sf::Color::White);
	text_[1].setString("New Game");
	text_[1].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 2));

	text_[2].setFont(font_);
	text_[2].setColor(sf::Color::White);
	text_[2].setString("Exit");
	text_[2].setPosition(sf::Vector2f(width / 2, height / (3 + 1) * 3));

	selectedIndex_ = 0;
}

Menu::~Menu()
{
    //Nothing to do here yet.
}

void Menu::MoveUp()
{
	if (selectedIndex_ - 1 >= 0) //If we are under 0 we have to MoveDown.
	{
		text_[selectedIndex_].setColor(Color::White);
		selectedIndex_--;
		text_[selectedIndex_].setColor(Color::Red);
	}
}

void Menu::MoveDown() 
{
	if (selectedIndex_ + 1 < 3) //If we are above 3 we have to MoveUP.
	{
		text_[selectedIndex_].setColor(sf::Color::White);
		selectedIndex_++;
		text_[selectedIndex_].setColor(sf::Color::Red);
	}
}

void Menu::Draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(text_[i]);
	}
}