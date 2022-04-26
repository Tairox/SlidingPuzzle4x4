#include "game.h"

Game::Game()
{
    window_.create(VideoMode(height, width), "Sliding Puzzle", Style::Default);
    window_.setFramerateLimit(60);
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