//
// Created by minaei on 4/5/2024.
//

#ifndef PROJECT_OPTIONSSCREEN_H
#define PROJECT_OPTIONSSCREEN_H
#include "CONFIG.h"
#include "GameLooptyLoop.h"
#include "MapObserver.h"
#include "State.h"

class OptionsScreen: public State {
public:
    explicit OptionsScreen(MainDataRef data);

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
        Sprite mute;
        Sprite back;
        Sprite music1;
        Sprite music2;
        Sprite music3;
        Sprite music4;
        RectangleShape music;
        Text musicText;
    };

    shared_ptr<Buttons> buttons = make_shared<Buttons>();

    void handleMusic();

    void SetButtons();

    void changeMusic(string fileName);

    static void GenerateButton(Sprite& button, Vector2f position, Texture& texture);
    static void GenerateButton(const Font &font, const string &name, RectangleShape &button, Text &buttonText, Vector2f position);
};


#endif//PROJECT_OPTIONSSCREEN_H
