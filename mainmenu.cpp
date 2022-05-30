#include "mainmenu.h"


MainMenu::MainMenu(RenderWindow & rw) : rw_(rw) //L'opérateur = n'existe pas pour la classe RenderWindow, on est donc obligé d'utiliser le constructeur de copie.
{
}


void MainMenu::init()
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
		//Handle error
	}
	title_.setFont(fontTitle_);
    sf::Color colorTitle(5,128,247);//Couleur RGB
	title_.setFillColor(colorTitle);
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

    if (!bufferSelect_.loadFromFile("sound/select_menu.ogg"))
    {
        //Handle error
    }
    soundSelect_.setBuffer(bufferSelect_);

    if (!bufferEnter_.loadFromFile("sound/enter_menu.ogg"))
    {
        //Handle error
    }
    soundEnter_.setBuffer(bufferEnter_);
}

void MainMenu::processInput()
{
    sf::Vector2i mousePosition;//position souris
    mousePosition=sf::Mouse::getPosition(rw_);
    unsigned int oldSelectedIndex=selectedIndex_;

    if(text_[0].getGlobalBounds().contains(rw_.mapPixelToCoords((mousePosition))))
    {
        selectedIndex_=0;
    }
    else
    {
        if(text_[1].getGlobalBounds().contains(rw_.mapPixelToCoords((mousePosition))))
        {
            selectedIndex_=1;
        }
        else
        {
            if(text_[2].getGlobalBounds().contains(rw_.mapPixelToCoords((mousePosition))))
            {
                selectedIndex_=2;
            }
        }
    }
    if(oldSelectedIndex!=selectedIndex_)
    {
        soundSelect_.play();
    }

    Event ev;
    
    isExitButtonPressed_=false;
    isPlayButtonPressed_=false,
    isNewGameButtonPressed_=false;
    while (rw_.pollEvent(ev))
    {
        switch (ev.type)
        {
        case Event::MouseButtonPressed:
            switch (selectedIndex_)
                {
                case 0:
                    isPlayButtonPressed_ = true;
                    soundEnter_.play();
                    break;
                case 1:
                    isNewGameButtonPressed_ = true;
                    soundEnter_.play();
                    break;
                case 2:
                    isExitButtonPressed_ = true;
                    soundEnter_.play();
                    break;
                default: //Dans les autres cas on ne fait rien
                    break;
                }
            break;
        case Event::KeyPressed:
            switch (ev.key.code)
            {
            case Keyboard::Up:
                if (selectedIndex_ - 1 >= 0)
                {
                    selectedIndex_--;
                    soundSelect_.play();
                }
                break;

            case Keyboard::Down:
                if (selectedIndex_ + 1 < 3)
                {
                    selectedIndex_++;
                    soundSelect_.play();
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
                    soundEnter_.play();
                    break;
                case 1:
                    isNewGameButtonPressed_ = true;
                    soundEnter_.play();
                    break;
                case 2:
                    isExitButtonPressed_ = true;
                    soundEnter_.play();
                    break;
                default: //Dans les autres cas on ne fait rien
                    break;
                }
                break;
            
            case Keyboard::P:
                isPlayButtonPressed_=true;
                break;

            case Keyboard::N:
                isNewGameButtonPressed_=true;
                break;

            case Keyboard::E:
                isExitButtonPressed_=true;
                break;
            default: //Dans les autres cas on ne fait rien
                break;
            }
            break;

        case sf::Event::Closed:
            rw_.close();
            break;

        default: //Dans les autres cas on ne fait rien
            break;
        }
    }
}

void MainMenu::update()
{
    sf::Color colorMenuSelected(255,0,193);//Couleur RGB
    for(unsigned int i = 0;i<3;i++)
    {
        text_[i].setFillColor(Color::White);
		text_[i].setStyle(Text::Regular);
        text_[i].setFont(font_);
    }
    text_[selectedIndex_].setFillColor(colorMenuSelected);
    text_[selectedIndex_].setFont(fontTitle_);
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
        //On ne fait rien
    }
}

void MainMenu::draw()
{
    rw_.clear(Color::Black);
    rw_.draw(bg_sprite_);
    rw_.draw(title_);
    for (int i = 0; i < 3; i++)
    {
    	rw_.draw(text_[i]);
    }
    rw_.display();
}

bool MainMenu::isInMenu()
{
    if(isNewGameButtonPressed_ || isPlayButtonPressed_)
    {return false;}
    else
    {return true;}
}