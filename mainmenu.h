#ifndef __mainmenu_h__
#define __mainmenu_h__

#include <SFML/Graphics.hpp>
using namespace sf;

#include "state.h"

class MainMenu : public State
{
private:
    Font font_;
    Text text_[3];
    int selectedIndex_;
    Text title;
	Font font;
	Vector2f titlePosition;
    float xVelocity = 3;

    Texture bg_texture;
    Sprite bg_sprite;

    bool isExitButtonPressed_ = false;
    bool isPlayButtonPressed_ = false;;
    bool isNewGameButtonPressed_ = false;

    RenderWindow & rw_;

public:
    MainMenu(RenderWindow &);

    void Init() override;
    void ProcessInput() override;
    void Update() override;
    void Draw() override;
};

#endif