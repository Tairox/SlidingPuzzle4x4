#include "game.h"

Game::Game()
{
    RenderWindow window(VideoMode(1920, 1080), "Sliding Puzzle", Style::Default);
    window.setFramerateLimit(60);
    mainMenu_ = new MainMenu(window);
    stateManager_ = new StateMan;
    stateManager_->Add(mainMenu_);
}

Game::~Game()
{
    delete stateManager_;
    delete mainMenu_;
}

void Game::Run()
{
    while(mainMenu_->getRenderWindow().isOpen())
    {
        stateManager_->ProcessStateChange();
        stateManager_->GetCurrent()->ProcessInput();
        stateManager_->GetCurrent()->Update();
        stateManager_->GetCurrent()->Draw();
    }
}