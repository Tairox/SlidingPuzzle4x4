#include "grid.h"

Grid::Grid(RenderWindow &RW) : rw(RW) //L'opérateur = n'existe pas pour la classe RenderWindow, on est donc obligé d'utiliser le constructeur de copie.
{

}

void Grid::Init()
{
    //rien pr l'instant
}

void Grid::ProcessInput()
{
    Event ev;
    
    while (rw.pollEvent(ev))
    {
        switch (ev.type)
        {

        case sf::Event::Closed:
            rw.close();
            break;
        }
    }
}

void Grid::Update()
{

}

void Grid::Draw()
{
    rw.clear(Color::Black);
    std::vector<RectangleShape> lines;

    unsigned int width=rw.getSize().x; // ici 1920
    unsigned int height=rw.getSize().y; //ici 1080
    unsigned int margeW=560; //marge qu'on laisse de chaque côté de la fenêtre (ça fera donc un carré de 800x800)
    unsigned int sizeLine=(width-margeW)-(0+margeW);// ici 1920-560 - 560 =  1360 - 560 = 800, on aura donc des traits de 800px de long
    unsigned int gap = sizeLine /4; //car on dessine 4 traits après le premier donc 800/4=200
    unsigned int margeH=140;//marge qu'on laisse en haut et en bas

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
    // Affichage
    for (size_t i = 0; i < lines.size(); i++)
    {
        rw.draw(lines[i]);
    }
    rw.display();
}