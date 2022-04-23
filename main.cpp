#include <SFML/Graphics.hpp>
#include"fct.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    sf::CircleShape shape(100.f);
<<<<<<< HEAD
    //shape.setFillColor(sf::Color::Green);
    couleurcercle(shape);
=======
    shape.setFillColor(sf::Color::Green);
    int a=3;
    a++;
>>>>>>> a8f41653066407c2e404b81cc1cef59e21ca2f16

    sf::Texture t;
    sf::Sprite s; 

    if(!t.loadFromFile("img/lena.jpg")) //la texture t a chargé l'image
    {
        //message d'erreur si image introuvable
    }

    s.setTexture(t); // le sprite contient la texture t

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(s);
        window.draw(shape);
        shape.setPosition(sf::Vector2f(1500,200));
        window.display();
    }
    return 0;
}