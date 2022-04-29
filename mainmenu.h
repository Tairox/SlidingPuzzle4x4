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

    Music music_;


    RenderWindow & rw_;

public:
    MainMenu(RenderWindow &);

    void Init() override;
    void ProcessInput() override;
    void Update() override;
    void Draw() override;
    bool isInMenu();
    bool isplayPressed() {return isPlayButtonPressed_;}
    bool isNewGamePressed() {return isNewGameButtonPressed_;}
};

#endif