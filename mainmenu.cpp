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

    if (!fontTitle_.loadFromFile("font/Walk-Around-the-Block.ttf"))
	{
		// handle error
	}
	title_.setFont(fontTitle_);
	title_.setFillColor(sf::Color::Red);
	title_.setString("Sliding Puzzle");
	title_.setCharacterSize(150);
    titlePosition_.x = 0;
    titlePosition_.y = 0;
	title_.setPosition(titlePosition_);

    if(!bg_texture_.loadFromFile("img/background.jpg"))
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
    for(unsigned int i = 0;i<3;i++)
    {
        text_[i].setFillColor(Color::White);
		//text_[i].setCharacterSize(100);
		text_[i].setStyle(Text::Regular);
    }
    text_[selectedIndex_].setFillColor(Color::Red);
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
        isInMenu_=false;// quand on clique on sort du menu

        /*
        int puzzle[4][4];
        unsigned int i=0; ce code sera fait dans une classe
        while (i<17)
        {
            for(unsigned int j=0;j<4;j++)
            {
                for(unsigned int k=0;k<4;k++)
                {
                    puzzle[j][k]=i;
                    i++;
                }
            }
        }*/
        

    }
}

void MainMenu::Draw()
{
    if(isInMenu_==true)//on dessine le menu
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

    if(isInMenu_==false)//on dessine le jeu
    {
        rw_.clear();
        rw_.display();
    }
}


