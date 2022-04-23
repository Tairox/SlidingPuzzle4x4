#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    int a=2;
    a++;

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