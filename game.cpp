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
    grid->Init();
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
            grid->Update();
            grid->Draw();
        }
	}
}

Game::~Game()
{
    delete mainMenu_;
    delete grid;
}

void Game::CheckIsInMenu()
{
    if(isInMenu)
    {
    isInMenu=mainMenu_->isInMenu();
    }
    //else isInMenu=grid->isInMenu();
}

void Game::save()
{
    // Sauvegarde à la fermeture de l'application :
    // On vérifie que l'utilisateur n'est pas resté dans le menu :

    if(mainMenu_->isInMenu())
    {
        // Ne pas sauvegarder
    }
    else
    {
        ofs.open("save/save.txt"); //Ouverture du fichier de sauvegarde dans ofs.
        if(!ofs.is_open())
        {
            //Handle error
        }
        else
        {
            for(unsigned int i=0;i<16;i++)
            {
                ofs<<grid->getPuzzle()[i]<<endl;
            }
            if(!ofs.good())
            {
                cout<<"Erreur d'écriture"<<endl;
            }
            else
            {
                cout<<"Enregistrement réussis"<<endl;
            }
        }
        
    } 
    delete grid->getPuzzle(); // Bien penser à supprimer le pointeur de grid ici ou pas ?
}