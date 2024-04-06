/**
 * @file MainMenu.h
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 * @brief
 */

#ifndef A2_MAINMENU_H
#define A2_MAINMENU_H

#include "CONFIG.h"
#include "GameLooptyLoop.h"
#include "SFML/Graphics.hpp"
#include "State.h"
#include "sstream"
#include <iostream>
#include "CharacterCreator.h"
using namespace sf;


class MainMenu : public State{
public:
    explicit MainMenu(MainDataRef data);

    void Init() override;
    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw(float deltaTime) override;

private:
    MainDataRef _data;

    Clock _clock; // Keeps track of time passed

    Texture _bgTexture;
    Sprite _bg;
    struct Buttons {
        RectangleShape play;
        Text playText;
        RectangleShape editMap;
        Text editMapText;
        RectangleShape createCharacter;
        Text createCharacterText;
        RectangleShape editCharacter;
        Text editCharacterText;
        RectangleShape load;
        Text loadText;
        RectangleShape options;
        Text optionsText;
        RectangleShape quit;
        Text quitText;
    };

    shared_ptr<Buttons> buttons = make_shared<Buttons>();


    void SetButtons();

    static void GenerateButton(const Font &font, const string &name, RectangleShape &button, Text &buttonText, Vector2f position);
};




#endif//A2_MAINMENU_H
