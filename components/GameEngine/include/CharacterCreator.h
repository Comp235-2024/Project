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

/**
 * @class CharacterCreator
 * @brief Represents the character creation state in the game.
 *
 * The CharacterCreator class is responsible for allowing the player to create a character
 * by selecting a character type. It inherits from the State class and implements the necessary
 * methods to handle input, update the state, and draw the character creation screen.
 */
class CharacterCreator : public State {
public:
    /**
     * @brief Constructs a CharacterCreator object.
     * @param data The main data reference containing shared resources.
     */
    explicit CharacterCreator(MainDataRef data);

    /**
     * @brief Initializes the character creator state.
     */
    void Init() override;

    /**
     * @brief Handles the user input in the character creator state.
     */
    void HandleInput() override;

    /**
     * @brief Updates the character creator state.
     * @param deltaTime The time elapsed since the last update.
     */
    void Update(float deltaTime) override;

    /**
     * @brief Draws the character creator state.
     * @param deltaTime The time elapsed since the last draw.
     */
    void Draw(float deltaTime) override;

    /**
     * @brief Creates a character of the specified type.
     * @param type The type of character to create.
     */
    void CreateCharacter(const std::string& type);

    /**
     * @brief Displays a message on the character creation screen.
     * @param message The message to display.
     */
    void DisplayCreationMessage(const std::string& message);

private:
    shared_ptr<Map> _currentMap; /**< The current map. */
    RenderTexture _mapTexture; /**< The texture for rendering the map. */
    RenderTexture _characterView; /**< The texture for rendering the character view. */
    RenderTexture _consoleView; /**< The texture for rendering the console view. */
    MainDataRef _data; /**< The main data reference containing shared resources. */
    Texture _bgTexture; /**< The background texture. */
    Sprite _bg; /**< The background sprite. */
    MapObserver mapObserver; /**< The map observer. */

    /**
     * @struct Buttons
     * @brief Represents the buttons for selecting character types.
     */
    struct Buttons {
        RectangleShape CreateNimble; /**< The button for creating a nimble character. */
        Text CreateNimbleText; /**< The text for the nimble character button. */
        RectangleShape CreateBully; /**< The button for creating a bully character. */
        Text CreateBullyText; /**< The text for the bully character button. */
        RectangleShape CreateTank; /**< The button for creating a tank character. */
        Text CreateTankText; /**< The text for the tank character button. */
    };

    shared_ptr<Buttons> buttons = make_shared<Buttons>(); /**< The buttons for selecting character types. */

    /**
     * @brief Generates the texture for rendering the map.
     */
    void generateMapTexture();

    /**
     * @brief Sets up the buttons for selecting character types.
     */
    void SetButtons();

    /**
     * @brief Generates a button with the specified font, name, position, and text.
     * @param font The font to use for the button text.
     * @param name The name of the button.
     * @param button The rectangle shape representing the button.
     * @param buttonText The text displayed on the button.
     * @param position The position of the button.
     */
    static void GenerateButton(const Font &font, const string &name, RectangleShape &button, Text &buttonText, Vector2f position);

    // Additional attributes for UI components go here
};

#endif//PROJECT_CHARACTERCREATOR_H