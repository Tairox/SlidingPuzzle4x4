#include "game.h"

Game::Game()
{
    window_.create(VideoMode(1920, 1080), "Sliding Puzzle", Style::Default);
    window_.setFramerateLimit(60);
    mainMenu_ = new MainMenu(window_);
    mainMenu_->Init();
}

void Game::run()
{
    while(window_.isOpen())
    {
		mainMenu_->ProcessInput();
		mainMenu_->Update();
		mainMenu_->Draw();
	}
}

Game::~Game()
{
    delete mainMenu_;
}