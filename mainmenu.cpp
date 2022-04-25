#include "mainmenu.h"


MainMenu::MainMenu(RenderWindow & rw) : rw_(rw)
{
}

void MainMenu::Init()
{
    if (!font_.loadFromFile("font/Walk-Around-the-Block.ttf"))
	{
		// handle error
	}

	text_[0].setFont(font_);
	text_[0].setColor(sf::Color::Red);
	text_[0].setString("Play");
	text_[0].setCharacterSize(150);
	text_[0].setStyle(sf::Text::Bold | sf::Text::Underlined);
	text_[0].setPosition(sf::Vector2f((rw_.getSize().x / 2) - (text_[0].getLocalBounds().width /2), rw_.getSize().y / (3 + 1) * 1));

	text_[1].setFont(font_);
	text_[1].setColor(sf::Color::White);
	text_[1].setString("New Game");
	text_[1].setCharacterSize(100);
	text_[1].setPosition(sf::Vector2f((rw_.getSize().x / 2) - (text_[1].getLocalBounds().width /2), rw_.getSize().y / (3 + 1) * 2));

	text_[2].setFont(font_);
	text_[2].setColor(sf::Color::White);
	text_[2].setString("Exit");
	text_[2].setCharacterSize(100);
	text_[2].setPosition(sf::Vector2f((rw_.getSize().x / 2) - (text_[2].getLocalBounds().width /2), rw_.getSize().y / (3 + 1) * 3));

	selectedIndex_ = 0;

    if (!font.loadFromFile("font/Walk-Around-the-Block.ttf"))
	{
		// handle error
	}
	title.setFont(font);
	title.setColor(sf::Color::Red);
	title.setString("Sliding Puzzle");
	title.setCharacterSize(150);
    titlePosition.x = 0;
    titlePosition.y = 0;
	title.setPosition(titlePosition);

    if(!bg_texture.loadFromFile("img/background.jpg"))
	{
		//Handle error
	}
    bg_sprite.setTexture(bg_texture);
}

void MainMenu::ProcessInput()
{
    Event ev;
    
    while (rw_.pollEvent(ev))
    {
        switch (ev.type)
        {
        case Event::KeyReleased:
            switch (ev.key.code)
            {
            case Keyboard::Up:
                if (selectedIndex_ - 1 >= 0)
                {
                    selectedIndex_--;
                }
                break;

            case Keyboard::Down:
                if (selectedIndex_ + 1 < 3)
                {
                    selectedIndex_++;
                }
                break;
            case Keyboard::Escape:
                isExitButtonPressed_ = true;
                break;
            case Keyboard::Enter:
                switch (selectedIndex_)
                {
                case 0:
                    isPlayButtonPressed_ = true;
                    break;
                case 1:
                    isNewGameButtonPressed_ = true;
                    break;
                case 2:
                    isExitButtonPressed_ = true;
                    break;
                }
                break;
            }
            break;

        case sf::Event::Closed:
            rw_.close();
            break;
        }
    }
}

void MainMenu::Update()
{
    for(unsigned int i = 0;i<3;i++)
    {
        text_[i].setColor(Color::White);
		text_[i].setCharacterSize(100);
		text_[i].setStyle(Text::Regular);
    }
    text_[selectedIndex_].setColor(Color::Red);
	text_[selectedIndex_].setCharacterSize(150);
	text_[selectedIndex_].setStyle(sf::Text::Bold | sf::Text::Underlined);

    //Physics
    if(titlePosition.x <0 || titlePosition.x > rw_.getSize().x - title.getLocalBounds().width)
    {
        xVelocity *= -1;
    }
    titlePosition.x += xVelocity;
    title.setPosition(titlePosition);

    //Buttons
    if(isExitButtonPressed_)
    {
        rw_.close();
    }
}

void MainMenu::Draw()
{
    rw_.clear(Color::Black);

	rw_.draw(bg_sprite);
	rw_.draw(title);
    for (int i = 0; i < 3; i++)
	{
		rw_.draw(text_[i]);
	}

    rw_.display(); //Tells app window is done drawing
}


