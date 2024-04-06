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


/**
 * @class MainMenu
 * @brief Represents the main menu state of the game.
 * 
 * The MainMenu class inherits from the State class and provides
 * functionality for initializing, handling input, updating, and drawing
 * the main menu state of the game.
 */
class MainMenu : public State{
public:
    /**
     * @brief Constructs a MainMenu object.
     * @param data The reference to the main data of the game.
     */
    explicit MainMenu(MainDataRef data);

    /**
     * @brief Initializes the main menu state.
     */
    void Init() override;

    /**
     * @brief Handles the input for the main menu state.
     */
    void HandleInput() override;

    /**
     * @brief Updates the main menu state.
     * @param deltaTime The time elapsed since the last update.
     */
    void Update(float deltaTime) override;

    /**
     * @brief Draws the main menu state.
     * @param deltaTime The time elapsed since the last draw.
     */
    void Draw(float deltaTime) override;

private:
    MainDataRef _data; ///< The reference to the main data of the game.

    Clock _clock; ///< Keeps track of time passed.

    Texture _bgTexture; ///< The background texture.
    Sprite _bg; ///< The background sprite.

    /**
     * @struct Buttons
     * @brief Represents the buttons in the main menu.
     */
    struct Buttons {
        RectangleShape play; ///< The play button.
        Text playText; ///< The text on the play button.
        RectangleShape editMap; ///< The edit map button.
        Text editMapText; ///< The text on the edit map button.
        RectangleShape createCharacter; ///< The create character button.
        Text createCharacterText; ///< The text on the create character button.
        RectangleShape editCharacter; ///< The edit character button.
        Text editCharacterText; ///< The text on the edit character button.
        RectangleShape load; ///< The load button.
        Text loadText; ///< The text on the load button.
        RectangleShape options; ///< The options button.
        Text optionsText; ///< The text on the options button.
        RectangleShape quit; ///< The quit button.
        Text quitText; ///< The text on the quit button.
    };

    shared_ptr<Buttons> buttons = make_shared<Buttons>(); ///< The buttons in the main menu.

    /**
     * @brief Sets up the buttons in the main menu.
     */
    void SetButtons();

    /**
     * @brief Generates a button with the specified font, name, position, and text.
     * @param font The font to use for the button text.
     * @param name The name of the button.
     * @param button The button shape to generate.
     * @param buttonText The text on the button.
     * @param position The position of the button.
     */
    static void GenerateButton(const Font &font, const string &name, RectangleShape &button, Text &buttonText, Vector2f position);
};




#endif//A2_MAINMENU_H
