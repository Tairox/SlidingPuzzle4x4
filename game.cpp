#include "game.h"

Game::Game()
{
    window_.create(VideoMode(height_, width_), "Sliding Puzzle", Style::Default);
    window_.setFramerateLimit(60);

    Image icon;
	if(!icon.loadFromFile("img/icon.png"))
	{
		//error
	}
	window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); //permet de définir l'icône de la fenêtre à partir d'un sf::Image

     if (!music_.openFromFile("music/MainMenuMusic.wav"))
    {
        //Handle error
    }
    music_.setVolume(50);
    music_.setLoop(true);
    music_.play();

    mainMenu_ = new MainMenu(window_);
    mainMenu_->init();
    grid_ = new Grid(window_);
    grid_->init();
}

void Game::run()
{
    while(window_.isOpen())
    {
        if(isInMenu_)
        {
            checkIsInMenu();
            mainMenu_->processInput();
            if(mainMenu_->isplayPressed())
            {
                charge();
            }

            if(mainMenu_->isNewGamePressed())
            {
                grid_->shuffle();
            }

            mainMenu_->update();
            mainMenu_->draw();
        }
        else
        {
            checkIsInMenu();
            grid_->processInput();
            grid_->update();
            grid_->draw();
            save(); //auto save
        }
	}
}

Game::~Game()
{
    delete mainMenu_;
    delete grid_;
    //delete sender_;
}

void Game::checkIsInMenu()
{
    if(isInMenu_)
    {
        isInMenu_=mainMenu_->isInMenu();
        if(!isInMenu_)//si on sort du menu
        {
            grid_->startClock();//on met la clock à 0
        }
    }
    else
    {
        isInMenu_=grid_->isInMenu();
    }
}

void Game::save()
{
    // Sauvegarde à la fermeture de l'application :
    ofs_.open("save/save.txt"); //Ouverture du fichier de sauvegarde dans ofs_.
    if(!ofs_.is_open())
    {
        cerr<<"Impossible d'ouvrir la sauvegarde"<<endl;
    }
    else
    {
        for(unsigned int i=0;i<16;i++)
        {
            ofs_<<grid_->getPuzzle()[i]<<endl;
        }
        if(!ofs_.good())
        {
            cerr<<"Erreur d'écriture"<<endl;
        }
        else
        {
            cout<<"Enregistrement réussi"<<endl;
        }
        ofs_.close();
    }
    //delete grid_->getPuzzle(); // Bien penser à supprimer le pointeur de grid_
}

void Game::charge()
{
    sender_ = new int[16];

    ifs_.open("save/save.txt");
    if(!ifs_.is_open())
    {
        cout<<"Erreur d'ouverture"<<endl;
    }
    else
    {
        for(unsigned int i=0;i<16;i++)
        {
            ifs_>>sender_[i];
        }
        if(!ifs_.good())
        {
            cerr<<"Erreur de lecture"<<endl;
        }
        else
        {
            cout<<"Lecture terminée"<<endl;
            grid_->setPuzzle(sender_);
        }
        ifs_.close();
    }
}