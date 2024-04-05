//
// Created by Khalil Azaiez on 2024-03-30.
//

#ifndef PROJECT_CHARACTERCREATOR_H
#define PROJECT_CHARACTERCREATOR_H

#include "CONFIG.h"
#include "GameLooptyLoop.h"
#include "MapObserver.h"
#include "State.h"
#include "MainMenu.h"
using namespace sf;



class CharacterCreator : public State {
public:
    explicit CharacterCreator(MainDataRef data);
    void Init() override;
    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw(float deltaTime) override;
    void CreateCharacter(const std::string& type);
    void DisplayCreationMessage(const std::string& message);

private:
    shared_ptr<Map> _currentMap; /**< The current map. */
    RenderTexture _mapTexture; /**< The texture for rendering the map. */
    RenderTexture _characterView; /**< The texture for rendering the character view. */
    RenderTexture _consoleView; /**< The texture for rendering the console view. */
    MainDataRef _data;
    Texture _bgTexture;
    Sprite _bg;
    MapObserver mapObserver; /**< The map observer. */


    struct Buttons {
        RectangleShape CreateNimble;
        Text CreateNimbleText;
        RectangleShape CreateBully;
        Text CreateBullyText;
        RectangleShape CreateTank;
        Text CreateTankText;

    };
    shared_ptr<Buttons> buttons = make_shared<Buttons>();


    void generateMapTexture();

    void SetButtons();
    static void GenerateButton(const Font &font, const string &name, RectangleShape &button, Text &buttonText, Vector2f position);

    // Additional attributes for UI components go here
};

#endif//PROJECT_CHARACTERCREATOR_H