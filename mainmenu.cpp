#include "mainmenu.h"


MainMenu::MainMenu(RenderWindow & rw) : rw_(rw) //L'opérateur = n'existe pas pour la classe RenderWindow, on est donc obligé d'utiliser le constructeur de copie.
{
}


void MainMenu::Init()
{
    if (!font_.loadFromFile("font/Retrofuturism.otf"))
	{
		// handle error
	}
	text_[0].setFont(font_);
	text_[0].setFillColor(sf::Color::Red);
	text_[0].setString("Play");
	text_[0].setCharacterSize(100);
	text_[0].setStyle(sf::Text::Bold | sf::Text::Underlined);
	text_[0].setPosition(sf::Vector2f((rw_.getSize().x / 2) - (text_[0].getLocalBounds().width /2), rw_.getSize().y / (3 + 1) * 1));

	text_[1].setFont(font_);
	text_[1].setFillColor(sf::Color::White);
	text_[1].setString("New Game");
	text_[1].setCharacterSize(100);
	text_[1].setPosition(sf::Vector2f((rw_.getSize().x / 2) - (text_[1].getLocalBounds().width /2), rw_.getSize().y / (3 + 1) * 2));

	text_[2].setFont(font_);
	text_[2].setFillColor(sf::Color::White);
	text_[2].setString("Exit");
	text_[2].setCharacterSize(100);
	text_[2].setPosition(sf::Vector2f((rw_.getSize().x / 2) - (text_[2].getLocalBounds().width /2), rw_.getSize().y / (3 + 1) * 3));

	selectedIndex_ = 0;

    if (!fontTitle_.loadFromFile("font/SFAlienEncounters-Italic.ttf"))
	{
		// handle error
	}
	title_.setFont(fontTitle_);
    sf::Color colorTitle(5,128,247);//couleur RGB
	title_.setFillColor(colorTitle);
	title_.setString("Sliding Puzzle");
	title_.setCharacterSize(150);
    titlePosition_.x = 0;
    titlePosition_.y = 0;
	title_.setPosition(titlePosition_);

    if(!bg_texture_.loadFromFile("img/background.png"))
	{
		//Handle error
	}
    bg_sprite_.setTexture(bg_texture_);
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
    sf::Color colorMenuSelected(255,0,193);//couleur RGB
    for(unsigned int i = 0;i<3;i++)
    {
        text_[i].setFillColor(Color::White);
		//text_[i].setCharacterSize(100);
		text_[i].setStyle(Text::Regular);
        text_[i].setFont(font_);
    }
    text_[selectedIndex_].setFillColor(colorMenuSelected);
    text_[selectedIndex_].setFont(fontTitle_);
	//text_[selectedIndex_].setCharacterSize(150);
	text_[selectedIndex_].setStyle(sf::Text::Bold | sf::Text::Underlined);

    //Physics
    if(titlePosition_.x <0 || titlePosition_.x > rw_.getSize().x - title_.getLocalBounds().width)
    {
        xVelocity_ *= -1;
    }
    titlePosition_.x += xVelocity_;
    title_.setPosition(titlePosition_);

    //Buttons
    if(isExitButtonPressed_)
    {
        rw_.close();
    }

    if(isNewGameButtonPressed_)
    {
        //rien
    }
}

void MainMenu::Draw()
{
    rw_.clear(Color::Black);
    rw_.draw(bg_sprite_);
    rw_.draw(title_);
    for (int i = 0; i < 3; i++)
    {
    	rw_.draw(text_[i]);
    }
    rw_.display(); //Tells app window is done drawing
}

bool MainMenu::isInMenu()
{
    if(isNewGameButtonPressed_)
    {return false;}
    else
    {return true;}
}

