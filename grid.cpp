#include<cstdlib>//génération random
#include<ctime> //génération random
#include"grid.h"
#include <string>
using namespace std;

Grid::Grid(RenderWindow &RW) : rw(RW) //L'opérateur = n'existe pas pour la classe RenderWindow, on est donc obligé d'utiliser le constructeur de copie.
{

}

void Grid::Init()
{
    //chargement de la police
    if (!font.loadFromFile("font/Retrofuturism.otf"))
	{
		// handle error
	}
    
    unsigned int width=rw.getSize().x; // ici 1920
    unsigned int height=rw.getSize().y; //ici 1080
    unsigned int sizeLine=(width-margeW)-(0+margeW);// ici 1920-560 - 560 =  1360 - 560 = 800, on aura donc des traits de 800px de long
    unsigned int gap = sizeLine /4; //car on dessine 4 traits après le premier donc 800/4=200
    
    //création du puzzle (1,2,3,4,...,16) on consid-re 16 la case vide
    unsigned int i=1;
    for(unsigned int j=0;j<4;j++)
   {
      for(unsigned int k=0;k<4;k++)
      {
        if(isGridSet==false)
        {
            puzzle[j][k].setString(std::to_string(i)); // on convertit l'int i en string "i"
        }
        puzzle[j][k].setFont(font); // on définit la police de tout les éléments
        puzzle[j][k].setCharacterSize(150);
        //on définit la position de chaque élément de la grille
        puzzle[j][k].setPosition(560+gap/4+gap*k,140+gap*j);
        i++;
      }
   }
   if(isGridSet==false)
   {
       PosFree = new int[2];
       SetFree();
       Shuffle();
   }
    isGridSet=true;

    if (!bufferWin_.loadFromFile("sound/SIUU.wav"))
    {
        //Handle error
    }
    soundWin_.setBuffer(bufferWin_);

    // création de 5 lignes verticales |
    for (unsigned int i = 0; i < 5; i++)
    {
        lines.push_back(RectangleShape(Vector2f(6, sizeLine)));
    }

    // 5 lignes horizontales —
    for (unsigned int i = 0; i < 5; i++)
    {
        lines.push_back(sf::RectangleShape(sf::Vector2f(sizeLine, 6)));
    }

    // Positionnement des lignes verticales
    for (unsigned int i = 0; i < 5; i++)
    {
        lines[i].setPosition(margeW+gap*i,margeH);
    }
    // Positionnement des lignes horizontales
    for (unsigned int i = 0; i < 5; i++)
    {
        lines[i+5].setPosition(margeW,margeH+gap*i);
    }

    // On colorie les lignes en blanc
    for (size_t i = 0; i < lines.size(); i++)
    {
        lines[i].setFillColor(sf::Color::White);
    }
}

void Grid::ProcessInput()
{
    isExitButtonPressed=false;
    Event ev;
    
    while (rw.pollEvent(ev))
    {
        switch (ev.type)
        {
        
        case Event::KeyPressed:
            if(ev.key.code==Keyboard::Escape)
            {
                isExitButtonPressed=true;
            }
            break;

        case sf::Event::Closed:
            rw.close();
            break;

        case sf::Event::MouseButtonPressed: // clic gauche
            sf::Vector2i mousePosition = sf::Mouse::getPosition(rw);
            if (mousePosition.x>margeW && mousePosition.x<1360 && mousePosition.y>margeH && mousePosition.y<940)
            {   //si on est dans la grille
                SetFree();//on récupère la pos de la case vide
                mousePosition.x=(mousePosition.x - margeW)/200;//[i] de [i][j] 3
                mousePosition.y=(mousePosition.y -margeH)/200;//[j] de [i][j] 2
                if(mousePosition.x==PosFree[1] && (mousePosition.y)+1==PosFree[0]) //case du dessous est vide
                {
                    MoveDown(mousePosition.x,mousePosition.y); //on fait baisser la case cliquée
                }
                if(mousePosition.x==PosFree[1] && (mousePosition.y)-1==PosFree[0]) //case du dessus est vide
                {
                    MoveUp(mousePosition.x,mousePosition.y); //on fait monter la case cliquée
                }
                if((mousePosition.x)+1==PosFree[1] && (mousePosition.y)==PosFree[0]) //case à droite vide
                {
                    MoveRight(mousePosition.x,mousePosition.y); //on fait aller à droite la case cliquée
                }
                if((mousePosition.x)-1==PosFree[1] && (mousePosition.y)==PosFree[0]) // case à gauche vide
                {
                    MoveLeft(mousePosition.x,mousePosition.y); // case cliquée va à gauche
                }

                checkIsResolved();
                if(isResolved)
                {
                    soundWin_.play();
                }
            }
            break;
        }
    }


}

void Grid::Update()
{
    checkIsResolved();
}

void Grid::Draw()
{
    rw.clear(Color::Black);
    // Affichage de la grille
    for (size_t i = 0; i < lines.size(); i++)
    {
        rw.draw(lines[i]);
    }
    //Affichage des chiffre de la grille
    /*puzzle[2][1].setFont(font);
    puzzle[2][1].setPosition(500,200);
    puzzle[2][1].setCharacterSize(100);
    rw.draw(puzzle[2][1]);*/
    for(unsigned int j=0;j<4;j++)
    {
        for(unsigned int k=0;k<4;k++)
        {
            if(puzzle[j][k].getString()!="16") //si c'est 16 alors c'est la case vide donc on ne l'affiche pas
            rw.draw(puzzle[j][k]);
        }
    }
    if(isResolved==true)
    {
        Text win;
        win.setFont(font);
        win.setString("WINNER WINNER CHICKEN DINNER");
        win.setCharacterSize(100);
        win.setPosition(380,20);
        rw.draw(win);
    }
    rw.display();
}

//Pour les méthodes Move : gérer les cas des bords (impossible d'aller à gauche etc)
void Grid::MoveUp(unsigned int x, unsigned int y) //pour faire monter la case cliquée d'un cran si la case cliquée est en dessous de la case vide
{
    String CaseCliquee = puzzle[y][x].getString();
    String CaseDuDessus = puzzle[y-1][x].getString();
    puzzle[y][x].setString(CaseDuDessus);
    puzzle[y-1][x].setString(CaseCliquee);
}

void Grid::MoveDown(unsigned int x, unsigned int y) //on fait baisser la case cliquée dans la case vide
{
    /*int* posFree;
    posFree=GetFree();//on récupère la position de la case vide
    if (posFree[0]!=3)//si on est pas sur la dernière ligne du taquin alors on peut faire l'opération MoveUp
    {   
        Text temp=puzzle[x][y];//on prend la case cliquée
        puzzle[x][y]=puzzle[x+1][y];//la case cliquée devient la case du dessous
        puzzle[x+1][y]=temp;//la case du dessus devient la case cliquée
    }*/
    String CaseCliquee = puzzle[y][x].getString();
    String CaseDuDessous = puzzle[y+1][x].getString();
    puzzle[y][x].setString(CaseDuDessous);
    puzzle[y+1][x].setString(CaseCliquee);
}

void Grid::MoveLeft(unsigned int x, unsigned int y) //case cliquée va à gauche
{
    /*int* posFree;
    posFree=GetFree();//on récupère la position de la case vide
    if (posFree[1]!=0) //si la case vide n'est pas sur la colonne de gauche 
    {
        Text temp=puzzle[x][y];
        puzzle[x][y]=puzzle[x][y-1];
        puzzle[x][y-1]=temp;
    }*/

    String CaseCliquee = puzzle[y][x].getString();
    String CaseDeGauche = puzzle[y][x-1].getString();
    puzzle[y][x].setString(CaseDeGauche);
    puzzle[y][x-1].setString(CaseCliquee);
    
}

void Grid::MoveRight(unsigned int x, unsigned int y) //case cliquée va à droite
{
    String CaseCliquee = puzzle[y][x].getString();
    String CaseDeDroite = puzzle[y][x+1].getString();
    puzzle[y][x].setString(CaseDeDroite);
    puzzle[y][x+1].setString(CaseCliquee);
}

void Grid::SetFree()
{
    for(unsigned int i=0;i<4;i++)
   {
      for(unsigned int j=0;j<4;j++)
      {
        if(puzzle[i][j].getString()=="16")
        {
            PosFree[0]=i;//y
            PosFree[1]=j;//x
        }
      }
   }
}

void Grid::Shuffle()
{
    SetFree();
    unsigned int max = 4; //nbr max-1
    srand(time(0));
    for(unsigned int i = 0; i<65535; i++) 
    {
        SetFree();
        unsigned int x=rand()%max;
        switch (x)
        {
        case 0:
            if(PosFree[0]!=0)
                MoveDown(PosFree[1],PosFree[0]-1);
            break;
        case 1:
            if(PosFree[0]!=3)
                MoveUp(PosFree[1],PosFree[0]+1);
            break;
        case 2:
            if(PosFree[1]!=0)
                MoveRight(PosFree[1]-1,PosFree[0]);
            break;
        case 3:
            if(PosFree[1]!=3)
             MoveLeft(PosFree[1]+1,PosFree[0]);
            break;
        default:
            //error
            break;
        }
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
        if(puzzle[j][k].getString()==std::to_string(i)) // si case=i
        {
            same++;
        }
        i++;
      }
   }
   if(same==16) //si toutes les cases sont dans le bon ordre
   {
       isResolved=true;
   }
   else
   {
       isResolved=false;
   }
}

int* Grid::getPuzzle()
{
    savePuzzle_ = new int [16];
    string text;
    for(unsigned int i=0;i<4;i++) // 4 itérations pour les 4 lignes
    {
        for(unsigned int j =0;j<4;j++) // 4 premières colonnes de la première ligne
        {
            text = puzzle[i][j].getString();
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
             puzzle[i][j].setString(std::to_string(sender[(i*4)+j]));
        }
    }
}

bool Grid::isInMenu()
{
    if(isExitButtonPressed)
    {
        return true;
    }
    else
    {
        return false;
    }
}