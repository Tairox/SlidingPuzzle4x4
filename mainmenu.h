/*------Auteur : Mattéo FIRRONE
        Contributeurs : Mattéo FIRRONE & Anthony De Sousa
        Date de dernière modification : 26.05.2022.
Type : Classe dérivée de la classe abstraite 'State'.
Rôle : Menu principale du jeu, la navigation permet à l'utilisateur de :
       - Choisir de jouer 'Play' avec la sauvegarde actuelle.
       - Lancer une nouvelle partie 'New Game'.
       - Quitter le jeu 'Exit'.
*/

#ifndef __mainmenu_h__
#define __mainmenu_h__

#include <SFML/Graphics.hpp>
using namespace sf;

#include <SFML/Audio.hpp>

#include "state.h"

class MainMenu : public State
{
private:
    Font font_;
    Text text_[3];
    int selectedIndex_;
    Text title_;
	Font fontTitle_;
	Vector2f titlePosition_;
    float xVelocity_ = 3;

    Texture bg_texture_;
    Sprite bg_sprite_;

    bool isExitButtonPressed_ = false;
    bool isPlayButtonPressed_ = false;;
    bool isNewGameButtonPressed_ = false;

    SoundBuffer bufferSelect_;
    Sound soundSelect_;
    SoundBuffer bufferEnter_;
    Sound soundEnter_;

    RenderWindow & rw_;

public:
    MainMenu(RenderWindow &);

    void init() override;
    void processInput() override;
    void update() override;
    void draw() override;
    bool isInMenu(); //renvoie vrai tant que nous n'avons pas appuyé sur l'un des boutons
    bool isplayPressed() {return isPlayButtonPressed_;}
    bool isNewGamePressed() {return isNewGameButtonPressed_;}
};

#endif