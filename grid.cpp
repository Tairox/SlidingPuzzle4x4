#include<cstdlib>//génération random
#include<ctime> //génération random
#include"grid.h"
#include <string>
using namespace std;

Grid::Grid(RenderWindow &RW) : rw_(RW) //L'opérateur = n'existe pas pour la classe RenderWindow, on est donc obligé d'utiliser le constructeur de copie.
{

}

Grid::~Grid()
{
    delete posFree_;
    delete savePuzzle_;
}

void Grid::init()
{
    //chargement de la police
    if (!font_.loadFromFile("font/Retrofuturism.otf"))
	{
		// handle error
	}
    if(!fontClock_.loadFromFile("font/digital-7.ttf"))
    {
        //error
    }
    
    srand(time(0)); //génération de la seed pour l'aléatoire
    //Chargement de l'image de fond dans une banque d'images
    changeBackground();// charge une image de fond

    unsigned int width_=rw_.getSize().x; // ici 1920
    unsigned int height_=rw_.getSize().y; //ici 1080
    unsigned int sizeLine=(width_-margeW_)-(0+margeW_);// ici 1920-560 - 560 =  1360 - 560 = 800, on aura donc des traits de 800px de long
    unsigned int gap = sizeLine /4; //car on dessine 4 traits après le premier donc 800/4=200
    //création du puzzle (1,2,3,4,...,16) on consid-re 16 la case vide
    unsigned int i=1;
    for(unsigned int j=0;j<4;j++)
   {
      for(unsigned int k=0;k<4;k++)
      {
        if(isGridSet_==false)
        {
            puzzle_[j][k].setString(std::to_string(i)); // on convertit l'int i en string "i"

            imgGrid[j][k].setTexture(bg_texture_);
            imgGrid[j][k].setTextureRect(IntRect(margeW_+206*k,margeH_+206*j,194,194));
            imgGrid[j][k].setPosition(margeW_+200*k,margeH_+200*j);
        }
        puzzle_[j][k].setFont(font_); // on définit la police de tout les éléments
        puzzle_[j][k].setCharacterSize(150);
        //on définit la position de chaque élément de la grille
        puzzle_[j][k].setPosition(560+gap/4+gap*k,140+gap*j);
        i++;
      }
   }
   if(!isGridSet_)
   {
       posFree_ = new int[2];
       getFree();
       shuffle();
   }
    isGridSet_=true;
    savePuzzle_ = new int [16];

    if (!bufferWin_.loadFromFile("sound/SIUU.wav"))
    {
        //Handle error
    }
    soundWin_.setBuffer(bufferWin_);

    // création de 5 lignes verticales |
    for (unsigned int i = 0; i < 4; i++)
    {
        lines_.push_back(RectangleShape(Vector2f(6, sizeLine)));
    }
    lines_.push_back(RectangleShape(Vector2f(6, sizeLine+6))); //la dernière ligne verticale doit être + longue car elle n'est pas recouverte par une ligne verticale
    // 5 lignes horizontales —
    for (unsigned int i = 0; i < 5; i++)
    {
        lines_.push_back(sf::RectangleShape(sf::Vector2f(sizeLine, 6)));
    }

    // Positionnement des lignes verticales
    for (unsigned int i = 0; i < 5; i++)
    {
        lines_[i].setPosition(margeW_+gap*i,margeH_);
    }
    // Positionnement des lignes horizontales
    for (unsigned int i = 0; i < 5; i++)
    {
        lines_[i+5].setPosition(margeW_,margeH_+gap*i);
    }

    // On colorie les lignes en blanc
    for (size_t i = 0; i < lines_.size(); i++)
    {
        lines_[i].setFillColor(sf::Color::White);
    }

    chrono_.setFont(fontClock_);
    chrono_.setPosition(200,120);
    chrono_.setCharacterSize(175);

    restartButton_.setFont(font_);
    restartButton_.setFillColor(Color::White);
    restartButton_.setPosition(1400,120);
    restartButton_.setCharacterSize(175);
    restartButton_.setString("Restart");

    backToMenuButton_.setFont(font_);
    backToMenuButton_.setFillColor(Color::White);
    backToMenuButton_.setPosition(80,20);
    backToMenuButton_.setCharacterSize(85);
    backToMenuButton_.setString("Back to menu");
}

void Grid::processInput()
{
    isExitButtonPressed_=false;
    Event ev;
    
    while (rw_.pollEvent(ev))
    {
        sf::Vector2i mousePosition;
        switch (ev.type)
        {
        
        case Event::KeyPressed:
            if(ev.key.code==Keyboard::Escape)
            {
                isExitButtonPressed_=true;
            }
            break;

        case sf::Event::Closed:
            rw_.close();
            break;

        case sf::Event::MouseButtonPressed: // clic gauche
            mousePosition = sf::Mouse::getPosition(rw_);
            if(restartButton_.getGlobalBounds().contains(rw_.mapPixelToCoords((mousePosition))))
            {
                shuffle();
                changeBackground();
                clock_.restart();
            }
            if(backToMenuButton_.getGlobalBounds().contains(rw_.mapPixelToCoords((mousePosition))))
            {
                isExitButtonPressed_=true;
            }
            if (mousePosition.x>margeW_ && mousePosition.x<1360 && mousePosition.y>margeH_ && mousePosition.y<940)
            {   //si on est dans la grille
                getFree();//on récupère la pos de la case vide
                mousePosition.x=(mousePosition.x - margeW_)/200;
                mousePosition.y=(mousePosition.y -margeH_)/200;
                if(mousePosition.x==posFree_[1] && (mousePosition.y)+1==posFree_[0]) //case du dessous est vide
                {
                    moveDown(mousePosition.x,mousePosition.y); //on fait baisser la case cliquée
                }
                if(mousePosition.x==posFree_[1] && (mousePosition.y)-1==posFree_[0]) //case du dessus est vide
                {
                    moveUp(mousePosition.x,mousePosition.y); //on fait monter la case cliquée
                }
                if((mousePosition.x)+1==posFree_[1] && (mousePosition.y)==posFree_[0]) //case à droite vide
                {
                    moveRight(mousePosition.x,mousePosition.y); //on fait aller à droite la case cliquée
                }
                if((mousePosition.x)-1==posFree_[1] && (mousePosition.y)==posFree_[0]) // case à gauche vide
                {
                    moveLeft(mousePosition.x,mousePosition.y); // case cliquée va à gauche
                }

                checkIsResolved();
                if(isResolved_)
                {
                    soundWin_.play();
                }
            }
            break;
        default:
            break;
        }
    }


}

void Grid::update()
{
    checkIsResolved();
    Time elapsed_ = clock_.getElapsedTime();
    if(!isResolved_)
    {
        minutes_ = elapsed_.asSeconds()/60;
        seconds_ = elapsed_.asSeconds()-60*minutes_;
    }
    else
    {
        clock_.restart();
    }
    string secondsString;
    if(seconds_<10)
    {
        secondsString="0"+std::to_string(seconds_);
    }
    else
    {
        secondsString=std::to_string(seconds_);
    }
    string minutesString =std::to_string(minutes_);
    chrono_.setString(minutesString+":"+secondsString);

    for (unsigned int j = 0; j < 4; j++)
    {
        for (unsigned int k = 0; k < 4; k++)
        {
            imgGrid[j][k].setPosition((margeW_+200*k)+6,(margeH_+200*j)+6);
        }
        
    }
}

void Grid::draw()
{
    rw_.clear(Color::Black);
    //rw_.draw(bg_sprite_);
    if(isResolved_)
    {
        rw_.draw(bg_sprite_);
        rw_.draw(bg_sprite_);// on la dessine une deuxième fois pour avoir 100% de luminosité
        Text win;
        win.setFont(font_);
        win.setString("WINNER WINNER CHICKEN DINNER");
        win.setCharacterSize(100);
        win.setPosition(380,20);
        rw_.draw(win);
        for(unsigned int j=0;j<4;j++)
        {
            for(unsigned int k=0;k<4;k++)
            {
                puzzle_[j][k].setFillColor(Color::Green);
            }
        }
    }
    else
    {
        for(unsigned int j=0;j<4;j++)
        {
            for(unsigned int k=0;k<4;k++)
            {
                puzzle_[j][k].setFillColor(Color::White);
            }
        }
    }
    // Affichage de la grille
    for (size_t i = 0; i < lines_.size(); i++)
    {
        rw_.draw(lines_[i]);
    }
    //Affichage des chiffre de la grille
    for(unsigned int j=0;j<4;j++)
    {
        for(unsigned int k=0;k<4;k++)
        {
            if(puzzle_[j][k].getString()!="16") //si c'est 16 alors c'est la case vide donc on ne l'affiche pas
            {
                rw_.draw(imgGrid[j][k]);
                rw_.draw(puzzle_[j][k]);
            }
        }
    }
    rw_.draw(chrono_);
    rw_.draw(restartButton_);
    rw_.draw(backToMenuButton_);
    rw_.display();
}

//Pour les méthodes Move : gérer les cas des bords (impossible d'aller à gauche etc)
void Grid::moveUp(unsigned int x, unsigned int y) //pour faire monter la case cliquée d'un cran si la case cliquée est en dessous de la case vide
{
    String CaseCliquee = puzzle_[y][x].getString();
    String CaseDuDessus = puzzle_[y-1][x].getString();
    puzzle_[y][x].setString(CaseDuDessus);
    puzzle_[y-1][x].setString(CaseCliquee);

    Sprite caseClic = imgGrid[y][x];
    imgGrid[y][x]=imgGrid[y-1][x];
    imgGrid[y-1][x]=caseClic;

}

void Grid::moveDown(unsigned int x, unsigned int y) //on fait baisser la case cliquée dans la case vide
{
    /*int* posFree_;
    posFree_=GetFree();//on récupère la position de la case vide
    if (posFree_[0]!=3)//si on est pas sur la dernière ligne du taquin alors on peut faire l'opération moveUp
    {   
        Text temp=puzzle_[x][y];//on prend la case cliquée
        puzzle_[x][y]=puzzle_[x+1][y];//la case cliquée devient la case du dessous
        puzzle_[x+1][y]=temp;//la case du dessus devient la case cliquée
    }*/
    String CaseCliquee = puzzle_[y][x].getString();
    String CaseDuDessous = puzzle_[y+1][x].getString();
    puzzle_[y][x].setString(CaseDuDessous);
    puzzle_[y+1][x].setString(CaseCliquee);

    Sprite caseClic = imgGrid[y][x];
    imgGrid[y][x]=imgGrid[y+1][x];
    imgGrid[y+1][x]=caseClic;
    
}

void Grid::moveLeft(unsigned int x, unsigned int y) //case cliquée va à gauche
{
    /*int* posFree_;
    posFree_=GetFree();//on récupère la position de la case vide
    if (posFree_[1]!=0) //si la case vide n'est pas sur la colonne de gauche 
    {
        Text temp=puzzle_[x][y];
        puzzle_[x][y]=puzzle_[x][y-1];
        puzzle[x][y-1]=temp;
    }*/

    String CaseCliquee = puzzle_[y][x].getString();
    String CaseDeGauche = puzzle_[y][x-1].getString();
    puzzle_[y][x].setString(CaseDeGauche);
    puzzle_[y][x-1].setString(CaseCliquee);

    Sprite caseClic = imgGrid[y][x];
    imgGrid[y][x]=imgGrid[y][x-1];
    imgGrid[y][x-1]=caseClic;
}

void Grid::moveRight(unsigned int x, unsigned int y) //case cliquée va à droite
{
    String CaseCliquee = puzzle_[y][x].getString();
    String CaseDeDroite = puzzle_[y][x+1].getString();
    puzzle_[y][x].setString(CaseDeDroite);
    puzzle_[y][x+1].setString(CaseCliquee);

    Sprite caseClic = imgGrid[y][x];
    imgGrid[y][x]=imgGrid[y][x+1];
    imgGrid[y][x+1]=caseClic;
}

void Grid::getFree()
{
    for(unsigned int i=0;i<4;i++)
   {
      for(unsigned int j=0;j<4;j++)
      {
        if(puzzle_[i][j].getString()=="16")
        {
            posFree_[0]=i;//y
            posFree_[1]=j;//x
        }
      }
   }
}

void Grid::shuffle()
{
    getFree();
    unsigned int max = 4; //nbr max-1
    for(unsigned int i = 0; i<65535; i++) 
    {
        getFree();
        unsigned int x=rand()%max;
        switch (x)
        {
        case 0:
            if(posFree_[0]!=0)
                moveDown(posFree_[1],posFree_[0]-1);
            break;
        case 1:
            if(posFree_[0]!=3)
                moveUp(posFree_[1],posFree_[0]+1);
            break;
        case 2:
            if(posFree_[1]!=0)
                moveRight(posFree_[1]-1,posFree_[0]);
            break;
        case 3:
            if(posFree_[1]!=3)
                moveLeft(posFree_[1]+1,posFree_[0]);
            break;
        default:
            //error
            break;
        }
    }
    
    //une fois le puzzle mélangé on ramène la case vide en bas à droite
    getFree();
    while(posFree_[0]!=3)
    {
        moveUp(posFree_[1],posFree_[0]+1);
        getFree();
    }

    while(posFree_[1]!=3)
    {
        moveLeft(posFree_[1]+1,posFree_[0]);
        getFree();
    }
}

void Grid::checkIsResolved()
{
    //création du puzzle (1,2,3,4,...,16) on consid-re 16 la case vide
    unsigned int same=0;
    unsigned int i=1;
    for(unsigned int j=0;j<4;j++)
    {
        for(unsigned int k=0;k<4;k++)
        {
        if(puzzle_[j][k].getString()==std::to_string(i)) // si case=i
        {
            same++;
        }
        i++;
        }
    }
    if(same==16) //si toutes les cases sont dans le bon ordre
    {
        isResolved_=true;
    }
    else
    {
        isResolved_=false;
    }
}

int* Grid::getPuzzle()
{
    string text;
    for(unsigned int i=0;i<4;i++) // 4 itérations pour les 4 lignes
    {
        for(unsigned int j =0;j<4;j++) // 4 premières colonnes de la première ligne
        {
            text = puzzle_[i][j].getString();
            savePuzzle_[(i*4)+j] = stoi(text);
        }
    }
    return savePuzzle_;
}

void Grid::setPuzzle(int* sender) //On ecrase la configuration initiale avec la nouvelle configuration chargée depuis la sauvegarde
{
    for(unsigned int i = 0; i<4;i++)
    {
        for(unsigned int j = 0; j<4;j++)
        {
            puzzle_[i][j].setString(std::to_string(sender[(i*4)+j]));
            int val= sender[(i*4)+j];
            int ligne=(val-1)/4;
            int colonne=((val-1)%4);
            imgGrid[i][j].setTexture(bg_texture_);
            imgGrid[i][j].setTextureRect(IntRect((margeW_+200*colonne)+6,(margeH_+200*ligne)+6,194,194)); //194 pour ne pas écrire sur les 6 de marge
        }
    }
}

bool Grid::isInMenu()
{
    if(isExitButtonPressed_)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Grid::startClock()
{
    clock_.restart();//remet la clock à 0
    //elapsed_.Zero;
}

void Grid::changeBackground()
{
    unsigned int x;
    do
    {
        x=rand()%9;
    } while (x==indiceImage_);
    indiceImage_=x;
    string path_background="img/grid_background/"+to_string(indiceImage_)+".png";
    if(!bg_texture_.loadFromFile(path_background))
	{
		//cerr error ?
	}
    bg_sprite_.setTexture(bg_texture_);
}