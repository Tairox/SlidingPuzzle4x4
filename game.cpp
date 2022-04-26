#include "game.h"

Game::Game()
{
    window_.create(VideoMode(height, width), "Sliding Puzzle", Style::Default);
    window_.setFramerateLimit(60);

    Image icon;
	if(!icon.loadFromFile("img/icon.png"))
	{
		//error
	}
	window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); //permet de définir l'icône de la fenêtre à partir d'un sf::Image

    mainMenu_ = new MainMenu(window_);
    mainMenu_->Init();
    grid = new Grid(window_);
}

void Game::run()
{
    while(window_.isOpen())
    {
        CheckIsInMenu();//si btn "new game" appuyé alors isInMenu devient false
        if(isInMenu==true)
        {
            mainMenu_->ProcessInput();
            mainMenu_->Update();
            mainMenu_->Draw();
        }
        else
        {
            grid->ProcessInput();
            grid->Draw();
        }
	}
}

Game::~Game()
{
    delete mainMenu_;
}

void Game::CheckIsInMenu()
{
    if(isInMenu)
    {
    isInMenu=mainMenu_->isInMenu();
    }
    //else isInMenu=grid->isInMenu();
}